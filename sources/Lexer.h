#pragma once
#include "Nodable.h"    // forward declarations
#include "Entity.h"       // base class
#include "Language.h"
#include <string>
#include <vector>

namespace Nodable{

	/*

		This class is build to generate a graph from an expression string.
		You just have to instantiate it and set its member "expression" and call update();

		auto ctx   = new Container("MyGlobalContainer");
		auto lexer = ctx->createLexer();
		lexer->setMember("expression", "10+50*40/0.001");
		lexer->update();		
		// here ctx should contain the generated graph.

	*/
	class Lexer : public Entity
	{
	private:

		/* This enum identifies each kind of Token the lexer can handle */
		enum TokenType_
		{
			TokenType_String   = 0,
			TokenType_Number   = 1,
			TokenType_Symbol   = 2,
			TokenType_Operator = 3,
			TokenType_Boolean  = 4,
			TokenType_Unknown  = 5
		};

		typedef struct
		{
			TokenType_  type      = TokenType_Unknown; // the type of the token
			std::string word      = "";                // the word as a string
			size_t      charIndex = 0;                 // the index of the first character of the token in the evaluated expression.
		}Token;

	public:
		Lexer(const Language* _language);
		virtual ~Lexer();

		/* Override from Entity class */
		bool           eval			       ();
	private:

		Member* operandTokenToMember(const Token& _token);

		Member* buildGraphIterative();
		/* To parse more than three tokens (ex: "1+59+1", "98*4*1", "true and false or true", etc...)*/
		Member* parseBinaryOperationExpressionEx(size_t _tokenId, Member* _leftOverride, Member* _rightOverride);

		/* To parse three tokens (ex: "1+59", "98*4", "true and false", etc...)*/
		Member* parseBinaryOperationExpression(size_t _tokenId, Member* _leftOverride, Member* _rightOverride);

		/** To parse two tokens (ex: !true, -5, etc..) */
		Member* parseUnaryOperationExpression(size_t _tokenId);

		/** To parse a primary expression (ex: "myVariable", "10.4", etc... ) */
		Member* parsePrimaryExpression(size_t _tokenId);

		/* Build a graph resursively starting at the token _tokenIndex reading up to _tokenIdMax tokens.*/
		Member*         parseExpression       (size_t _tokenIndex = 0, size_t _tokenCountMax = 0,   Member* _leftValueOverride = nullptr, Member* _rightValueOverride = nullptr);

		/* Cut the member "expression" into tokens to identifies its type (cf. TokenType_ enum) */
		void           tokenizeExpressionString			   ();

		/* Check if the existing tokens match with the syntax of the language. tokenize() should be called first */
		bool           isSyntaxValid	   ();
		
		/* Creates a new token given a _type, _string and _chanIndex and add it to the tokens.*/
		void           addToken			   (TokenType_ _type, std::string _string, size_t _charIndex);

		std::vector<Token> tokens;
		const Language* language;
	};

}