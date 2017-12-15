#ifndef __SD_FS_APP_H
#define	__SD_FS_APP_H

#include "ff.h"
#include "SSDlcd.h"

int8_t Sdfs_create				(char *new_file_name);
int8_t Sdfs_new						(char *new_file_name, 	 uint8_t *write_buffer, 	uint8_t buffer_size);
int8_t Sdfs_write					(char *write_file_name,  uint8_t *write_buffer, 	uint8_t buffer_size);
int8_t Sdfs_read					(char *read_file_name, 	 uint8_t *save_buffer);
int8_t GetNOInfo_fr_sd		(uint8_t *save_buffer);
int8_t GetCHInfo_fr_sd		(uint8_t *save_buffer);
int8_t GetGBKCode_from_sd	(uint8_t *pBuffer,const uint8_t *c);


#endif /* __SD_FS_PP_H */
