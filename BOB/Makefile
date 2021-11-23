rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CPPSourceCode = $(call rwildcard,Source,*.cpp)
ASMSourceCode = $(call rwildcard,Source,*.S)
Objects = $(patsubst Source/%.S, Build/%.so, $(ASMSourceCode))
Objects += $(patsubst Source/%.cpp, Build/%.o, $(CPPSourceCode))
Directories = $(wildcard Source/*)

Build/%.o: Source/%.cpp
	@-mkdir -p $(@D)
	gcc -fno-stack-protector -fPIC -fshort-wchar -mno-red-zone -Wall -c $^ -o $@ -fPIC

Build/%.so: Source/%.S
	@-mkdir -p $(@D)
	gcc -fno-stack-protector -fPIC -fshort-wchar -mno-red-zone -Wall -c $^ -o $@ -fPIC

all: $(Objects)
	gcc Build/crt0-efi-x86_64.so Build/relocation.o -m64 -nostdlib -fPIC -Tlinker.ld -e _start -o Build/bootx64.o
	objcopy -j .text          \
		-j .sdata               \
		-j .data                \
		-j .dynamic             \
		-j .dynsym              \
		-j .rel                 \
		-j .rela                \
		-j .reloc               \
		--target=efi-app-x86_64 Build/bootx64.o ../Build/ISO/EFI/BOOT/bootx64.efi