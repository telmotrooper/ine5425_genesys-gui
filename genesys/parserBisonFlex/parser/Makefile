all: parser lexer

parser:
	bison --graph=bisongraph.dot --locations --verbose --xml=bisonreport.xml --defines=../GenesysParser.h -o ../GenesysParser.cpp bisonparser.yy

lexer:
	flex --full -o ../Genesys++-scanner.cpp lexerparser.ll
