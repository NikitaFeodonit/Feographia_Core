/*
 * Project:  Feographia
 * Purpose:  Mobile application to work with the biblical text
 * Authors:  NikitaFeodonit, nfeodonit@yandex.com
 * ****************************************************************************
 * Copyright (C) 2015 NikitaFeodonit
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <pthread.h>

#include <android/log.h>

#include <jni.h>
#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "Fcore", fmt, ##__VA_ARGS__)

#include "fcore/Fcore.hpp"


// Redirect the "stdout" and "stderr" to android logcat.
// https://codelab.wordpress.com/2014/11/03/how-to-use-standard-output-streams-for-logging-in-android-apps/
// http://stackoverflow.com/a/31777050

static int logcat_pfd[2];
static pthread_t stdouts_thread;
static const char *logcat_tag;


static void *stdouts_thread_func(void*)
{
    ssize_t rdsz;
    char buf[256];

    // workaround for android logcat formatting
    buf[0] = '-';
    buf[1] = 'F';
    buf[2] = 'g';
    buf[3] = '-';
    buf[4] = ' ';

    int logPrefixSize = 5;

    while((rdsz = read(logcat_pfd[0], buf + logPrefixSize, sizeof buf - 1 - logPrefixSize)) > 0) {
//        if(buf[rdsz + 7 - 1 ] == '\n') --rdsz;
        buf[rdsz + logPrefixSize] = 0;  /* add null-terminator */
        __android_log_write(ANDROID_LOG_DEBUG, logcat_tag, buf);
    }
    return 0;
}


int redirect_stdouts_to_logcat(const char *app_name)
{
    logcat_tag = app_name;

    /* make stdout line-buffered and stderr unbuffered */
    setvbuf(stdout, 0, _IOLBF, 0);
    setvbuf(stderr, 0, _IONBF, 0);

    /* create the pipe and redirect stdout and stderr */
    pipe(logcat_pfd);
    dup2(logcat_pfd[1], 1);
    dup2(logcat_pfd[1], 2);

    /* spawn the logging thread */
    if(pthread_create(&stdouts_thread, 0, stdouts_thread_func, 0) == -1) {
        return -1;
    }

    pthread_detach(stdouts_thread);
    return 0;
}


extern "C" jbyteArray Java_ru_feographia_fcore_message_FcoreMsg_fcoreSendMessage(
        JNIEnv* env,
        jclass type,
        jobject segmentsQuery)
{
    void* segmentsPtrQ = env->GetDirectBufferAddress(segmentsQuery);
    long long int segmentSizeQ = env->GetDirectBufferCapacity(segmentsQuery);

    kj::Array<capnp::word> replyWords = Fcore::messageWorker(segmentsPtrQ, segmentSizeQ);
    kj::ArrayPtr<kj::byte> replyBytes = replyWords.asBytes();
    jbyte* segmentsPtrsR = (jbyte*) replyBytes.begin(); // TODO: c++ cast
    jsize segmentsSizesR = (jsize) replyBytes.size(); // TODO: c++ cast

    if (!segmentsPtrsR || !segmentsSizesR) {
        return nullptr;
    }

    jbyteArray segmentsReply = env->NewByteArray(segmentsSizesR);
    env->SetByteArrayRegion(segmentsReply, 0, segmentsSizesR, segmentsPtrsR);
    return segmentsReply;
}


extern "C" jlong Java_ru_feographia_fcore_Fcore_fcoreRunMainThread(JNIEnv* env, jobject thiz)
{
    redirect_stdouts_to_logcat("Fcore");

    LOG("-Fg- FC: main thread %s", "starting");
    jlong zmqContextPointer = (jlong) Fcore::runMainThread();
    LOG("-Fg- FC: main thread %s", "started");

    return zmqContextPointer;
}
