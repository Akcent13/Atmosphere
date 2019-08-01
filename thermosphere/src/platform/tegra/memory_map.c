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

#include "memory_map.h"
#include "../../utils.h"
#include "../../mmu.h"
#include "../../core_ctx.h"

// Limit ourselves to 34-bit addr space even if the tegra support up to 36 in theory
// i.e. 14GB of dram max
#define ADDRSPACESZ    34

static ALIGN(0x1000) u64 g_ttbl[BIT(ADDRSPACESZ - 30)] = {0};

static inline void identityMapL1(u64 *tbl, uintptr_t addr, size_t size, u64 attribs)
{
    mmu_map_block_range(1, tbl, addr, addr, size, attribs | MMU_PTE_BLOCK_INNER_SHAREBLE);
}

uintptr_t configureMemoryMap(u32 *addrSpaceSize)
{
    // QEMU virt RAM address space starts at 0x40000000
    *addrSpaceSize = ADDRSPACESZ;

    if (currentCoreCtx->isColdbootCore) {
        identityMapL1(g_ttbl, 0x00000000ull, 1ull << 30, ATTRIB_MEMTYPE_DEVICE);
        identityMapL1(g_ttbl, 0x40000000ull, 1ull << 30, ATTRIB_MEMTYPE_DEVICE);

        for (u64 i = 2; i < 16; i++) {
            identityMapL1(g_ttbl, i << 30, 1ull << 30, ATTRIB_MEMTYPE_NORMAL);
        }
    }

    return (uintptr_t)g_ttbl;
}