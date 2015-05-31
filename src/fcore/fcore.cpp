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

#include <boost/thread.hpp>
#include <zmq.hpp>

#include "fcore.hpp"


class FcoreMain
{
public:
        void operator()(zmq::context_t* context)
        {
            //  Prepare our context and socket
//            zmq::socket_t socket (*context, ZMQ_REP);
//            socket.bind ("tcp://127.0.0.1:7575");
            zmq::socket_t socket (*context, ZMQ_PAIR);
            socket.bind ("inproc://step3");

            while (true) {
                zmq::message_t request;

                //  Wait for next request from client
                socket.recv (&request);

                //  Send reply back to client
                zmq::message_t reply (5);
                memcpy ((void *) reply.data (), "World", 5);
                socket.send (reply);
                }
        }
};


void* fcoreRunMainThread()
{
    FcoreMain fcoreMain;
    zmq::context_t* context = new zmq::context_t(1);
    boost::thread fcoreMainThread(fcoreMain, context);

    void* ptr = *context; // void* ptr = context->ptr;
    return ptr;
}


void fcoreTestZeroMqReq(long context_p)
{
    zmq::context_t* context = (zmq::context_t*) context_p;

//    zmq::socket_t socket (*context, ZMQ_REQ);
//    socket.connect ("tcp://127.0.0.1:7575");
    zmq::socket_t socket (*context, ZMQ_PAIR);
    socket.connect ("inproc://step3");

    for (int request_nbr = 0; request_nbr < 5000; ++request_nbr) {
        zmq::message_t request (6);
        memcpy ((void *) request.data (), "Hello", 5);
        socket.send (request);

        zmq::message_t reply;
        socket.recv (&reply);
    }
}
