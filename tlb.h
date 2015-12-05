//
//  tlb.h
//
//
//  Created by Lucy Reynolds on 11/30/15.
//
//

#ifndef ____tlb__
#define ____tlb__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define OFFSET_BITS 8
#define OFFSET_MASK 0xFF
#define NUM_PAGES   256
#define NUM_FRAMES  256
#define PAGE_SIZE   256
#define TLB_SIZE    16
#define TRUE        1
#define FALSE       0

using namespace std;

typedef unsigned int page_t;
typedef unsigned int value_t;
typedef unsigned int frame_t;
typedef unsigned int offset_t;
typedef unsigned int logic_address_t;
typedef unsigned int physical_address_t;
typedef frame_t page_table_t[256];

typedef char physical_memory_t[256][256];

typedef vector<logic_address_t> logic_address_list_t;
typedef vector<physical_address_t> address_value_list_t;

bool physAdd;
bool FIFO;

ifstream instream;
ofstream outstream;

typedef struct {
    page_t  page_num;
    frame_t frame_num;
    bool    valid;
    int     created;
    int     used;
} tlb_entry_t;

typedef struct {
    tlb_entry_t tlb_entry[TLB_SIZE];
    unsigned int next_tlb_ptr;
} tlb_t;

int TLB_init(tlb_t* tlb);
int init_page_table(page_table_t page_table);
int TLB_replacement_FIFO(page_t page_num, frame_t frame_num, tlb_t* tlb);
int TLB_replacement_LRU(page_t p_num, frame_t f_num, tlb_t *tlb);
int TLB_display(tlb_t tlb);
int logic_address_loader(string logic_address_file_name, vector<logic_address_t> *logic_address_list);
int extract_logic_address(logic_address_t logic_address, page_t *page_num, offset_t *offset);
int TLB_hit_miss();
int search_TLB(page_t p_num, tlb_t tlb, bool *is_tlb_hit, frame_t *f_num);
int search_page_table(page_t p_num, page_table_t p_table, bool *is_page_fault, frame_t *f_num);
int is_TLB_hit();
int page_fault_handler(page_t p_num, frame_t frame_num, physical_memory_t *physical_mem, page_table_t *p_table, tlb_t *tlb);
int create_physical_address(frame_t frame_num, offset_t offset, physical_address_t *physical_address);
int read_physical_memory (physical_address_t p_addr, physical_memory_t physical_mem, value_t *value);
int update_address_value_list(logic_address_t l_addr, physical_address_t p_addr, value_t value, address_value_list_t addr_value_list);
int output_address_value_list(const char *output_file_name, address_value_list_t addr_value_list);
int load_frame_to_physical_memory(page_t page_num, string backing_store_file_name, physical_memory_t physical_memory, frame_t *frame_num);



#endif /* defined(____tlb__) */
