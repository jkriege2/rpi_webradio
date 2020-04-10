#ifndef CGDEBUG_H
#define CGDEBUG_H
#include <string>
#include <iostream>
#include <stdint.h>

/** \brief RAII construct for DEBUG-output of block-runtime */

struct CGBlockLogger {
	private:
		std::string m_blockname;
	public:
	    inline CGBlockLogger(const std::string& blockname): 
			m_blockname(blockname) 
		{
			std::cout<<m_blockname<<": STARTING ...\n";
		}
		
		inline ~CGBlockLogger() {
			std::cout<<m_blockname<<": DONE!\n";
		}
		
		inline void log(const std::string& text) {
			std::cout<<m_blockname<<": MESSAGE: "<<text<<"\n";
		}
};



#endif // CGDEBUG_H
