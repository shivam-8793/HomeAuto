idf_component_register(SRCS "state_table.c"
                    INCLUDE_DIRS "include"
					REQUIRES "nvs_flash"
                    PRIV_REQUIRES "main")
