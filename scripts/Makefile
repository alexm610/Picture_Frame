# Toolchain
CC := /opt/ti-cgt-arm_20.2.5.LTS/bin/armcl
LD := /opt/ti-cgt-arm_20.2.5.LTS/bin/armcl

TARGET := picture_frame

# Directories
SRC_DIR 	:= ../source
APP_DIR		:= $(SRC_DIR)/app
HAL_SRC_DIR := $(SRC_DIR)/halcogen/source
HAL_INC_DIR := $(SRC_DIR)/halcogen/include
BUILD_DIR := ../build

# Output file
OUT_ELF := $(BUILD_DIR)/$(TARGET).elf

APP_INC_DIRS := $(shell find $(APP_DIR) -type d)
APP_INCS 	:= $(patsubst %, --include_path%, $(APP_INC_DIRS))


# Compiler and linker flags
COMMON_FLAGS := -mv7R4 --code_state=32 --float_support=VFPv3D16 \
  --enum_type=packed --abi=eabi --display_error_number \
  --diag_wrap=off --diag_warning=225 -g

CFLAGS := $(COMMON_FLAGS) --preproc_with_compile \
  --include_path=$(HAL_INC_DIR) --include_path=$(HAL_SRC_DIR) \
   --include_path=/opt/ti-cgt-arm_20.2.5.LTS/include
CFLAGS += $(APP_INCS)

LDFLAGS := $(COMMON_FLAGS) -z --heap_size=0x800 --stack_size=0x800 \
  -i/opt/ti-cgt-arm_20.2.5.LTS/lib -i/opt/ti-cgt-arm_20.2.5.LTS/include \
  --reread_libs --warn_sections --rom_model --be32 \
  --xml_link_info=$(BUILD_DIR)/linkinfo.xml -m=$(BUILD_DIR)/mapfile.map \
  -o $(OUT_ELF)

# Source files
APP_SRCS	:= $(shell find $(APP_DIR) -name "*.c")
HAL_SRCS 	:= $(filter-out $(HAL_SRC_DIR)/sys_main.c, $(shell find $(HAL_SRC_DIR) -name '*.c'))
ASM_SRCS := $(shell find $(HAL_SRC_DIR) -name '*.asm')
#APP_INCS	:= $(shell find $(APP_DIR) -type d)

ALL_SRCS :=	$(APP_SRCS) \
			$(HAL_SRCS) \
			$(ASM_SRCS) 

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.obj, $(filter %.c,$(ALL_SRCS))) \
        $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.obj, $(filter %.s,$(ALL_SRCS))) \
		$(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.obj, $(filter %.asm,$(ALL_SRCS)))

FLASH_FLAGS := --verbose --flash --run

# Default target
all: $(OUT_ELF)

# Create build/ folder structure
$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) --preproc_dependency="$(basename $@).d_raw" --obj_directory=$(dir $@) $<

$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) --preproc_dependency="$(basename $@).d_raw" --obj_directory=$(dir $@) $<

$(BUILD_DIR)/%.obj: $(SRC_DIR)/%.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) --preproc_dependency="$(basename $@).d_raw" --obj_directory=$(dir $@) $<

# Link
$(OUT_ELF): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(HAL_SRC_DIR)/sys_link.cmd -lrtsv7R4_T_be_v3D16_eabi.lib

# Flash
flash: 
	dslite $(FLASH_FLAGS) --config=../utilities/TMS570LS1224.ccxml $(OUT_ELF)

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

-include $(OBJS:.obj=.d_raw)
