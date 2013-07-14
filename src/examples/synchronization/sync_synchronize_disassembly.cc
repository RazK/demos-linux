/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2013 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * linuxapi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * linuxapi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with linuxapi. If not, see <http://www.gnu.org/licenses/>.
 */

#include <firstinclude.h>
#include <stdlib.h>	// for EXIT_SUCCESS
#include <disassembly_utils.h>	// for disassemble_main()

/*
 * This is a demo to show how sync_synchronize() is implemented...
 * You should see the __sync_synchronize which is a machine memory barrier
 * translated to a "lock orl" instruction in assembly which is an instruction
 * to the core you are running on to stop reordering writes and reads
 * and drop all cache assumptions.
 * So you should see one instruction in the disassembly of this code.
 * And indeed this is what we see.
 *
 * Take note that this is a also a compiler barrier. It prevents the compiler
 * from reordering around this code and carrying assumptions across the barrier.
 * You don't see any assembly emitted for that since a compiler barrier is only
 * a compile time instruction about future code emittion.
 *
 * We also show how to code __sync_syncronize in direct assembly code.
 *
 * this is so disassembly will show interleaved code 
 * EXTRA_COMPILE_FLAGS=-g3
 */

int main(int argc, char** argv, char** envp) {
	__sync_synchronize();
	asm ("lock orl $0x0, (%esp)");
	disassemble_main();
	return EXIT_SUCCESS;
}