include .config.mk
all_OBJDIR =$(src_OBJDIR)
all_NAME   =src


# === Units ===
OBJ =$(patsubst %,%/*.o,$(all_OBJDIR))

# === Compiler ===
comp =$(CXX)
flag =$(CXX_flag)
link =


# === Build ===
$(bld_DIR)/$(bld_NAME): $(all_NAME)
	@mkdir -p $(bld_DIR)
	@echo "=== Linking Build ==="
	$(comp) $(OBJ) $(flag) $(inc) $(link) -o $(bld_DIR)/$(bld_NAME)

src:
	$(call RecurMake,$(src_DIR),)

# docs:
# 	$(MAKE) -C docs -s


# === Directory Management ===
clean:
	$(call RecurMake,$(src_DIR),clean)

	@echo "--- Cleaning Build ---"
	rm -f $(bld_DIR)/$(bld_NAME)

.PHONY: clean $(all_NAME)
