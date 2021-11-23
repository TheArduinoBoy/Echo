#include "Library/Memory.hpp"
#include "Library/SystemTable.hpp"
#include "Library/FileSystem.hpp"
#include "Library/String.hpp"
#include "Library/ELF.hpp"
#include "main.hpp"

extern "C" unsigned long long _relocate(long LDBase, ELFDynamicEntry* DynamicEntry, void* ImageHandle, void* SystemTable) {
  long relocationSize = 0, relocationEntry = 0;
  ELFRelocationEntry* relocation = 0;
  unsigned long* address;
  for (int i=0;DynamicEntry[i].d_tag!=0;i++) {
    switch (DynamicEntry[i].d_tag) {
      case 7:
        relocation = (ELFRelocationEntry*)((unsigned long)DynamicEntry[i].d_un.d_ptr + LDBase);
        break;
      case 8:
        relocationSize = DynamicEntry[i].d_un.d_val;
        break;
      case 9:
        relocationEntry = DynamicEntry[i].d_un.d_val;
        break;
      default: break;
    }
  }
  if (!relocation && relocationEntry == 0) return 0;
  if (!relocation || relocationEntry == 0) return 0x8000000000000001;
  while (relocationSize > 0) {
    switch (relocation->r_info & 0xffffffff) {
      case 0: break;
      case 8:
        address = (unsigned long*)(LDBase+relocation->r_offset);
        *address += LDBase;
        break;
      default: break;
    }
    relocation = (ELFRelocationEntry*)((char*)relocation + relocationEntry);
    relocationSize -= relocationEntry;
  }
  return 0;
}