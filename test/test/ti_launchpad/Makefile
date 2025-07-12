# Toolchain
CC := /opt/ti-cgt-arm_20.2.5.LTS/bin/armcl
LD := /opt/ti-cgt-arm_20.2.5.LTS/bin/armcl

# Directories
SRC_DIR := halcogen/source
INC_DIR := halcogen/include
BUILD_DIR := build

# Output file
OUT_ELF := $(BUILD_DIR)/output.elf

# Source files
C_SRCS := $(wildcard $(SRC_DIR)/*.c)
ASM_SRCS := $(wildcard $(SRC_DIR)/*.asm)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.obj,$(C_SRCS)) \
        $(patsubst $(SRC_DIR)/%.asm,$(BUILD_DIR)/%.obj,$(ASM_SRCS))

# Compiler and linker flags
COMMON_FLAGS := -mv7R4 --code_state=32 --float_support=VFPv3D16 \
  --enum_type=packed --abi=eabi --display_error_number \
  --diag_wrap=off --diag_warning=225 -g

CFLAGS := $(COMMON_FLAGS) --preproc_with_compile \
  --include_path=$(INC_DIR) --include_path=$(SRC_DIR) --include_path=/opt/ti-cgt-arm_20.2.5.LTS/include

LDFLAGS := $(COMMON_FLAGS) -z --heap_size=0x800 --stack_size=0x800 \
  -i/opt/ti-cgt-arm_20.2.5.LTS/lib -i/opt/ti-cgt-arm_20.2.5.LTS/include \
  --reread_libs --warn_sections --rom_model --be32 \
  --xml_link_info=linkinfo.xml -m=mapfile.map \
  -o $(OUT_ELF)

# Default target
all: $(OUT_ELF)

# Create build folder
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile C
$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) --preproc_dependency=$(BUILD_DIR)/$*.d_raw --obj_directory=$(BUILD_DIR) $<

# Assemble ASM
$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	$(CC) $(CFLAGS) --preproc_dependency=$(BUILD_DIR)/$*.d_raw --obj_directory=$(BUILD_DIR) $<

# Link
$(OUT_ELF): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(SRC_DIR)/sys_link.cmd -lrtsv7R4_T_be_v3D16_eabi.lib

# Clean
clean:
	rm -rf $(BUILD_DIR)/*
	rm -f mapfile.map linkinfo.xml

.PHONY: all clean
