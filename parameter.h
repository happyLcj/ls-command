#define ALL_FILE 1     //-a
#define LONG_FORMAT 2  //-l
#define INODE 4        //-i
#define IS_ALL(pamter) (pamter&ALL_FILE)
#define IS_LONG(pamter) (pamter&LONG_FORMAT)
#define IS_INODE(pamter) (pamter&INODE)