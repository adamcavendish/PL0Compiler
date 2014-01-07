#include <tokenizer/WordMap.hpp>

namespace PL0 {

WordMap::WordMap() :
	m_word_map({
			{ "begin",		Token::tk_begin			},
			{ "call",		Token::tk_call			},
			{ "const",		Token::tk_const			},
			{ "do",			Token::tk_do			},
			{ "end",		Token::tk_end			},
			{ "if",			Token::tk_if			},
			{ "odd",		Token::tk_odd			},
			{ "procedure",	Token::tk_procedure		},
			{ "read",		Token::tk_read			},
			{ "then",		Token::tk_then			},
			{ "var",		Token::tk_var			},
			{ "while",		Token::tk_while			},
			{ "write",		Token::tk_write			}
	}),
	m_operator_pool("+-*/=#<>()"),
	m_operator_map({
			{ "+",			{ Token::tk_plus,			precedence(20)	}	},
			{ "-",			{ Token::tk_minus,			precedence(20)	}	},
			{ "*",			{ Token::tk_multiply,		precedence(30)	}	},
			{ "/",			{ Token::tk_divide,			precedence(30)	}	},
			{ "=",			{ Token::tk_equal,			precedence(10)	}	},
			{ "#",			{ Token::tk_notequal,		precedence(10)	}	},
			{ "<",			{ Token::tk_less,			precedence(10)	}	},
			{ "<=",			{ Token::tk_lessequal,		precedence(10)	}	},
			{ ">",			{ Token::tk_greater,		precedence(10)	}	},
			{ ">=",			{ Token::tk_greaterequal,	precedence(10)	}	},
			{ "(",			{ Token::tk_lparenthesis,	precedence(40)	}	},
			{ ")",			{ Token::tk_rparenthesis,	precedence(40)	}	}
	}),
	m_othersym_pool(",;.:"),
	m_othersym_map({
			{ ",",			Token::tk_comma			},
			{ ";",			Token::tk_semicolon		},
			{ ".",			Token::tk_period		},
			{ ":=",			Token::tk_assign		},
	})
{}

WordMap::~WordMap()
{}

}//namespace PL0

