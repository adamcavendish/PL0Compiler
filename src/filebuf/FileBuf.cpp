#include <filebuf/FileBuf.hpp>


namespace PL0 {

char
FileBuf::get() {
	char ret = m_pbuf->sgetc();

	if(this->check_at_newline(ret))
		ret = m_pbuf->snextc();

	if(ret == '\n' || ret == '\r')
		ret = '\n';
	return ret;
}//get()

char FileBuf::bump() {
	char ret = m_pbuf->sbumpc();

	if(this->check_at_newline(ret))
		ret = m_pbuf->sbumpc();

	m_last_char = ret;

	if(ret == '\n' || ret == '\r') {
		ret = '\n';
		++m_line_num;
		m_pos_num = 0;
	} else {
		++m_pos_num;
	}//if-else

	return ret;
}//bump()

char
FileBuf::next() {
	char ret = m_pbuf->sbumpc();

	if(this->check_at_newline(ret))
		ret = m_pbuf->sbumpc();

	m_last_char = ret;

	ret = m_pbuf->sgetc();

	if(this->check_at_newline(ret))
		ret = m_pbuf->snextc();

	m_last_char = ret;

	if(ret == '\n' || ret == '\r') {
		ret = '\n';
		++m_line_num;
		m_pos_num = 0;
	} else {
		++m_pos_num;
	}//if-else

	return ret;
}//next()

}//namespace PL0

