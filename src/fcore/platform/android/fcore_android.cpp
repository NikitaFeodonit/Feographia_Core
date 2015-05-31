/*******************************************************************************
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
 ******************************************************************************/

#include <jni.h>

#include <android/log.h>
#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "fcore", fmt, ##__VA_ARGS__)

#include "fcore/fcore.hpp"


extern "C"
void Java_ru_feographia_FCore_fcoreRunMainThread(JNIEnv* env, jobject thiz)
{
    LOG("main thread: %s", "starting");
    fcoreRunMainThread();
    LOG("main thread: %s", "started");
}


extern "C"
void Java_ru_feographia_FCore_fcoreTestZeroMqReq(JNIEnv* env, jobject thiz)
{
    fcoreTestZeroMqReq();
}
