#include <stdbool.h>
#include <string.h>

#include "html_table_parser.h"

Result get_html_table_tag_count(HTMLTagCount *htc, const char *html_str)
{
	unsigned int table_head_fit_count = 0;
	unsigned int tr_head_fit_count = 0;
	unsigned int th_head_fit_count = 0;
	unsigned int td_head_fit_count = 0;

	unsigned int table_tail_fit_count = 0;
	unsigned int tr_tail_fit_count = 0;
	unsigned int th_tail_fit_count = 0;
	unsigned int td_tail_fit_count = 0;

	unsigned int i = 0;
	unsigned int j = 0;

	Result result = { false, "" };
	memset(result.error_message, '\0', sizeof(RESULT_ERROR_MESSAGE_SIZE));

	while (*(html_str + i) != '\0') {
		for (j = 0; j < HTML_TABLE_HEAD_LENGTH; j++)
			if (HTML_TABLE_HEAD_STR[j] == *(html_str + i + j))
				table_head_fit_count++;

		for (j = 0; j < HTML_TABLE_TAIL_LENGTH; j++)
			if (HTML_TABLE_TAIL_STR[j] == *(html_str + i + j))
				table_tail_fit_count++;

		for (j = 0; j < HTML_TABLE_ELEMENT_HEAD_LENGTH; j++) {
			if (HTML_TR_HEAD_STR[j] == *(html_str + i + j))
				tr_head_fit_count++;

			if (HTML_TH_HEAD_STR[j] == *(html_str + i + j))
				th_head_fit_count++;

			if (HTML_TD_HEAD_STR[j] == *(html_str + i + j))
				td_head_fit_count++;
		}

		for (j = 0; j < HTML_TABLE_ELEMENT_TAIL_LENGTH; j++) {
			if (HTML_TR_TAIL_STR[j] == *(html_str + i + j))
				tr_tail_fit_count++;

			if (HTML_TH_TAIL_STR[j] == *(html_str + i + j))
				th_tail_fit_count++;

			if (HTML_TD_TAIL_STR[j] == *(html_str + i + j))
				td_tail_fit_count++;
		}

		if (table_head_fit_count == HTML_TABLE_HEAD_LENGTH)
			htc->table_head_occurrence++;

		if (tr_head_fit_count == HTML_TABLE_ELEMENT_HEAD_LENGTH)
			htc->tr_head_occurrence++;

		if (th_head_fit_count == HTML_TABLE_ELEMENT_HEAD_LENGTH)
			htc->th_head_occurrence++;

		if (td_head_fit_count == HTML_TABLE_ELEMENT_HEAD_LENGTH)
			htc->td_head_occurrence++;

		if (table_tail_fit_count == HTML_TABLE_TAIL_LENGTH)
			htc->table_tail_occurrence++;

		if (tr_tail_fit_count == HTML_TABLE_ELEMENT_TAIL_LENGTH)
			htc->tr_tail_occurrence++;

		if (th_tail_fit_count == HTML_TABLE_ELEMENT_TAIL_LENGTH)
			htc->th_tail_occurrence++;

		if (td_tail_fit_count == HTML_TABLE_ELEMENT_TAIL_LENGTH)
			htc->td_tail_occurrence++;

		i++;

		table_head_fit_count = 0;
		tr_head_fit_count = 0;
		th_head_fit_count = 0;
		td_head_fit_count = 0;

		table_tail_fit_count = 0;
		tr_tail_fit_count = 0;
		th_tail_fit_count = 0;
		td_tail_fit_count = 0;
	}

	if (htc->table_head_occurrence == htc->table_tail_occurrence &&
	    htc->tr_head_occurrence == htc->tr_tail_occurrence &&
	    htc->th_head_occurrence == htc->th_tail_occurrence &&
	    htc->td_head_occurrence == htc->td_tail_occurrence) {
		result.is_ok = true;
	} else {
		strncpy(result.error_message, "Malformed html table\n",
			sizeof(RESULT_ERROR_MESSAGE_SIZE));
	}

	return result;
}
