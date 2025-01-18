set(COLLECTION_ROOT_PATH   ${CMAKE_SOURCE_DIR}/Collections)

# The most of command 'll use  curses program  to perform 
# some terminal manipulation using termcapabilities  
find_package(Curses  REQUIRED) 

message(CHECK_START  "Looking dependancies")
if(NOT CURSES_FOUND) 
  message(CHECK_FAIL "Curses packages undefined on the system")  
  set(CMD_USE_CURSES "")
endif() 

message(CHECK_PASS "Curses packages found")  
set(CMD_USE_CURSES   ${CURSES_LIBRARY})

set(LS "Option to build ls command" ON)
set(LS_PATH_SOURCES  ${COLLECTION_ROOT_PATH}/_ls)
set(LS_USE_CURSES  ${CMD_USE_CURSES}) 
set(LS_CMD   uls)  
set(LS_SOURCE ${LS_PATH_SOURCES}/listing.c) 

set(CLS "Option to build clear command", ON)
set(CLS_PATH_SOURCES ${COLLECTION_ROOT_PATH}/_clear) 
set(CLS_CMD ucls)
set(CLS_SOURCE ${CLS_PATH_SOURCES}/clear.c) 
set(CLS_USE_CURSES ${CMD_USE_CURSES}) 

