#pragma once

#include "result.h"

#define HTML_TABLE_HEAD_LENGTH 7
#define HTML_TABLE_TAIL_LENGTH 8

#define HTML_TABLE_ELEMENT_HEAD_LENGTH 4
#define HTML_TABLE_ELEMENT_TAIL_LENGTH 5

#define HTML_TABLE_HEAD_STR "<table>"
#define HTML_TABLE_TAIL_STR "</table>"

#define HTML_TR_HEAD_STR "<tr>"
#define HTML_TR_TAIL_STR "</tr>"

#define HTML_TH_HEAD_STR "<th>"
#define HTML_TH_TAIL_STR "</th>"

#define HTML_TD_HEAD_STR "<td>"
#define HTML_TD_TAIL_STR "</td>"

typedef struct HTMLTagCount {
	unsigned int table_head_occurrence;
	unsigned int tr_head_occurrence;
	unsigned int th_head_occurrence;
	unsigned int td_head_occurrence;

	unsigned int table_tail_occurrence;
	unsigned int tr_tail_occurrence;
	unsigned int th_tail_occurrence;
	unsigned int td_tail_occurrence;
} HTMLTagCount;

Result get_html_table_tag_count(HTMLTagCount *htc, const char *html_str);
Result verify_html_table_architecture(char *html_str);

bool check_table_tag_architecture(char *html_table_block_str);
bool check_tr_tag_architecture(char *html_tr_block_str);
bool check_th_tag_architecture(char *html_th_block_str);
bool check_td_tag_architecture(char *html_td_block_str);
