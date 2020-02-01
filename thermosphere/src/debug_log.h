/*
 * Copyright (c) 2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <stdarg.h>

#ifndef NDEBUG
#define DEBUG(...)      debugLog(__VA_ARGS__)
#define DEBUGRAW(str)   debugLogRaw(str)
#else
#define DEBUG(...)
#define DEBUGRAW(str)
#endif

void debugLogInit(void);
void debugLogRaw(const char *str);
int debugLog(const char *fmt, ...);
