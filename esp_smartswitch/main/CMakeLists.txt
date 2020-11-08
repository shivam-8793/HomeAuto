idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
		              REQUIRES "port" "comm" "monitor" "control" "switch_table")
