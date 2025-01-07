include $(ROOT)/$(CONFIG_FILE)
sub_NAME    =  example
sub_DIR     =$(example_DIR)
sub_SRCDIR  =$(example_SRCDIR)
sub_HEADDIR =$(example_HEADDIR)


# === Units ===
SRC  =$(call FirstOrderSource,$(sub_SRCDIR),.c) 
HEAD =$(call FirstOrderSource,$(sub_HEADDIR),.h) 
OBJ  =$(call SourceToObject,$(SRC),$(obj_DIR))


# === Compiler ===
comp =$(CC)
flag =$(CC_flag) -c
inc  =-I$(sub_HEADDIR) -I$(src_HEADDIR)


# === Build ===
subdirectory: $(obj_DIR) $(OBJ)

.SECONDEXPANSION:
$(OBJ): $(obj_DIR)/%.o: $(call NameToSource,%,$(SRC),.c) $(HEAD)
	@echo "=== Compiling <$(notdir $<)> in <$(sub_NAME)> ==="
	$(comp) $< $(flag) $(inc) -o $@


# --- Directory Management ---
$(obj_DIR):
	@mkdir -p $(obj_DIR)

clean:
	@echo "=== Cleaning <$(sub_NAME)> ==="
	rm -f $(obj_DIR)/*.o

.PHONY: subdirectory clean
