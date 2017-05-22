/**
 * @file    flash_blob.c
 * @brief   Flash algorithm for medium-density stm32f10x8/stm32f10xB chips
 *
 * DAPLink Interface Firmware
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "flash_blob.h"

//static const uint32_t flash_prog_blob[] = {
//    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
//    0xf36f4943, 0x44490012, 0x48426008, 0x60012100, 0x60414941, 0x60414941, 0xf01069c0, 0xd1080f04, 
//    0xf245483f, 0x60015155, 0x60412106, 0x71fff640, 0x20006081, 0x48374770, 0xf0416901, 0x61010180, 
//    0x47702000, 0x69014833, 0x0104f041, 0x69016101, 0x0140f041, 0x68c16101, 0x0f01f011, 0xf64abf1c, 
//    0x4a2f21aa, 0x6011d004, 0xf01368c3, 0xd1fa0f01, 0xf0216901, 0x61010104, 0x47702000, 0x690a4925, 
//    0x0202f042, 0x6148610a, 0xf0406908, 0x61080040, 0xf01068c8, 0xbf1c0f01, 0x20aaf64a, 0xd0044a20, 
//    0x68cb6010, 0x0f01f013, 0x6908d1fa, 0x0002f020, 0x20006108, 0x1c494770, 0x0101f031, 0x4b15bf18, 
//    0xf8d3d024, 0xf04cc010, 0xf8c30c01, 0xf8b2c010, 0xf8a0c000, 0xf8d3c000, 0xf01cc00c, 0xd1fa0f01, 
//    0xc010f8d3, 0x0c01f02c, 0xc010f8c3, 0xc00cf8d3, 0x0f14f01c, 0x68d8d005, 0x0014f040, 0x200160d8, 
//    0x1c804770, 0xf1021e89, 0xd1da0202, 0x47702000, 0x00000004, 0x40022000, 0x45670123, 0xcdef89ab, 
//    0x40003000, 0x00000000, 0x00000000, 
//};

//static const program_target_t flash = {
//    0x20000021, // Init
//    0x20000057, // UnInit
//    0x20000065, // EraseChip
//    0x2000009D, // EraseSector
//    0x200000D7, // ProgramPage

//    // BKPT : start of blob + 1
//    // RSB  : blob start + header + rw data offset
//    // RSP  : stack pointer
//    {
//        0x20000000 + 0x00000001,
//        0x20000000 + 0x00000020 + 0x00000124,
//        0x20000800
//    },

//    0x20000000 + 0x00000A00,   // mem buffer location
//    0x20000000,                // location to write prog_blob in target RAM
//    sizeof(flash_prog_blob),   // prog_blob size
//    flash_prog_blob,           // address of prog_blob
//    0x00000200                 // ram_to_flash_bytes_to_be_written
//};


static const uint32_t stm32f4xx_2048_flash_prog_blob[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x03004601, 0x28200e00, 0x0940d302, 0xe0051d00, 0xd3022810, 0x1cc00900, 0x0880e000, 0xd50102c9,
    0x43082110, 0x48524770, 0x60414950, 0x60414951, 0x22f068c1, 0x60c14311, 0x06806940, 0x484fd406,
    0x6001494d, 0x60412106, 0x6081494d, 0x47702000, 0x68084947, 0x021b231f, 0x439a4602, 0x6008600a,
    0x054a6908, 0x61084310, 0x47702000, 0x4840b410, 0x24046901, 0x61014321, 0x03a26901, 0x61014311,
    0x03c968c1, 0x493fd505, 0x60114a3c, 0x03db68c3, 0x6901d4fb, 0x610143a1, 0x2000bc10, 0x03014770,
    0x0e09b430, 0xd3022920, 0x1d090949, 0x2910e005, 0x0909d302, 0xe0001cc9, 0x02c00889, 0x2010d501,
    0x482b4301, 0x24f068c2, 0x60c24322, 0x61052502, 0x06c96902, 0x430a0e09, 0x69016102, 0x431103ea,
    0x68c16101, 0xd50503c9, 0x4a244926, 0x68c36011, 0xd4fb03db, 0x43a96901, 0x68c16101, 0x0f090609,
    0x68c1d005, 0x60c14321, 0x2001bc30, 0xbc304770, 0x47702000, 0x4d16b470, 0x08891cc9, 0x008968eb,
    0x433326f0, 0x230060eb, 0x2900612b, 0x4b16d01b, 0x431c692c, 0x6814612c, 0x68ec6004, 0xd4fc03e4,
    0x0864692c, 0x612c0064, 0x062468ec, 0xd0050f24, 0x433068e8, 0xbc7060e8, 0x47702001, 0x1f091d00,
    0x29001d12, 0xbc70d1e4, 0x47702000, 0x45670123, 0x40023c00, 0xcdef89ab, 0x00005555, 0x40003000,
    0x00000fff, 0x0000aaaa, 0x00000201, 0x00000000
};

static const program_target_t flash = {
    0x20000047, // Init
    0x20000071, // UnInit
    0x2000008d, // EraseChip
    0x200000bf, // EraseSector
    0x20000135, // ProgramPage

    // BKPT : start of blob + 1
    // RSB  : blob start + header + rw data offset
    // RSP  : stack pointer
    {
        0x20000001,
        0x200001ac,
        0x20000800
    },

    0x20000000 + 0x00000A00,  // mem buffer location
    0x20000000,               // location to write prog_blob in target RAM
    sizeof(stm32f4xx_2048_flash_prog_blob),   // prog_blob size
    stm32f4xx_2048_flash_prog_blob,           // address of prog_blob
    0x00000400       // ram_to_flash_bytes_to_be_written
};



