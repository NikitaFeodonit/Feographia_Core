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

#ifndef FCORE_HPP
#define FCORE_HPP

#include <zmq.hpp>


extern const char* INPROC_FCORE;

extern const int32_t MSG_TYPE_UNKNOWN;
extern const int32_t MSG_TYPE_GET_CHAPTER_TEXT;
extern const int32_t MSG_TYPE_ERROR;
extern const int32_t MSG_TYPE_GET_FILE_TEXT;


void fcoreMain();
void* fcoreRunMainThread();


#endif // FCORE_HPP
