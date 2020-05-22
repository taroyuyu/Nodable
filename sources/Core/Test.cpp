#include <memory> // for unique_ptr

#include "Test.h"
#include "Member.h"
#include "Log.h"
#include "Node.h"
#include "Wire.h"
#include "DataAccess.h"
#include "Container.h"
#include "Language.h"
#include "Parser.h"
#include "Variable.h"

using namespace Nodable;

int  Test::s_testCount        = 0;
int  Test::s_testSucceedCount = 0;

void Test::ResetCounters()
{
	s_testCount        = 0;
	s_testSucceedCount = 0;
}

void Test::DisplayResults()
{
	LOG_MESSAGE("---------------------------------------------------------------\n");
	if(s_testSucceedCount != s_testCount)
		LOG_MESSAGE("   Some tests failed. Passed : %d / %d\n", s_testSucceedCount, s_testCount);
	else
		LOG_MESSAGE("   All tests are OK : %d / %d\n", s_testSucceedCount, s_testCount);

	LOG_MESSAGE("---------------------------------------------------------------\n");
}

bool Test::RunAll()
{
	LOG_MESSAGE("---------------------------------------------------------------\n");
	LOG_MESSAGE("--                   Testing Nodable                         --\n");
	LOG_MESSAGE("---------------------------------------------------------------\n");
	LOG_MESSAGE("-- Info: note that these tests do NOT cover all the code     --\n");
	LOG_MESSAGE("---------------------------------------------------------------\n");
	ResetCounters();

	LOG_MESSAGE("Running Test for Value class: \n");

	LOG_MESSAGE(" - Connection Flags...\n");

	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(Connection_In);

		if (!v->allows(Connection_Out)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-1a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(Connection_InOut)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-1b : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_In)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-1c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_None)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-1d : FAILED !\n");
		}
		s_testCount++;
	}


	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(Connection_Out);

		if (v->allows(Connection_Out)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-2a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(Connection_InOut)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-2b : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(Connection_In)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-2c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_None)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-2d : FAILED !\n");
		}
		s_testCount++;
	}

	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(Connection_None);

		if (!v->allows(Connection_Out)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-3a : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(Connection_InOut)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-3b : FAILED !\n");
		}
		s_testCount++;

		if (!v->allows(Connection_In)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-3c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_None)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-3d : FAILED !\n");
		}
		s_testCount++;
	}


	{
		std::unique_ptr<Member> v(new Member);

		v->setConnectionFlags(Connection_InOut);

		if (v->allows(Connection_Out)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-4a : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_InOut)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-4b : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_In)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-4c : FAILED !\n");
		}
		s_testCount++;

		if (v->allows(Connection_None)){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°0-4d : FAILED !\n");
		}
		s_testCount++;
	}


	// Test 01 - Set/Get a boolean
	//----------------------------

	LOG_MESSAGE(" - Get/Set (Boolean)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue(true);		

		if (v->getValueAsBoolean()){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°1a : FAILED !\n");
		}
		s_testCount++;
		
		if (v->getType() == ::Type_Boolean){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°1b : FAILED !\n");
		}
		s_testCount++;

		v->setValue(false);
		if (!v->getValueAsBoolean()){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°1c : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°1d : FAILED !\n");
		}
		s_testCount++;
	}

	// Test 02 - Set/Get a string
	//---------------------------

	LOG_MESSAGE(" - Get/Set (String)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue("Hello world !");
		std::string str = "Hello world !";
		if (v->getValueAsString() == str){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°2a : FAILED !\n");
		}
		s_testCount++;

		if (v->getValueAsBoolean() == true){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°2b : FAILED !\n");
		}
		s_testCount++;

		if (v->getType() == ::Type_String){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°2c : FAILED !\n");
		}
		s_testCount++;

		if (v->getValueAsNumber() == str.length() ){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°2d : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°2e : FAILED !\n");
		}
		s_testCount++;
	}

	// Test 03 - Set/Get a number (double)
	//------------------------------------

	LOG_MESSAGE(" - Get/Set (Number)...\n");

	{
		std::unique_ptr<Member> v(new Member);
		v->setValue(50.0F);

		if (v->getValueAsNumber() == 50.0F){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°3a : FAILED !\n");
		}
		s_testCount++;

		if (v->getType() == ::Type_Number){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°3b : FAILED !\n");
		}
		s_testCount++;

		if (v->isSet()){
			s_testSucceedCount++;
		}else{
			LOG_ERROR("Test n°3c : FAILED !\n");
		}
		s_testCount++;
	}

	LOG_MESSAGE("Running Test for Node class...\n");

	{
		// Test 4 : set/get a node member :
		//---------------------------------

		std::unique_ptr<Node> a(new Node);
		a->add("v");
		a->setMember("v", double(100));
		
		if( a->get("v")->getValueAsNumber()  == double(100))
			s_testSucceedCount++;
		else
			LOG_ERROR("Test n°4 : FAILED !\n");
		s_testCount++;

	}

	LOG_MESSAGE("Running integration Tests for Wire and Node class...\n");

	{
		// Test 5a : connect two nodes (creates a wire)
		//---------------------------------------------

		std::unique_ptr<Node> a(new Node);
		a->add("output");

		std::unique_ptr<Node> b(new Node);
		b->add("input");
		
		std::unique_ptr<Wire> wire(new Wire);
		Node::Connect(wire.get(), a->get("output"), b->get("input"));

		if ( 	wire->getSource() 		== a->get("output") && 
				wire->getTarget() 		== b->get("input")
			)
			s_testSucceedCount++;
		else
			LOG_ERROR("Test n°5a : FAILED !\n");
		s_testCount++;

		// Test 5b : disconnect a wire
		//----------------------------

		Node::Disconnect(wire.get());
		if(wire->getSource() == nullptr && wire->getTarget() == nullptr )
			s_testSucceedCount++;
		else
			LOG_ERROR("Test n°5b : FAILED !\n");
		s_testCount++;

	}

	LOG_MESSAGE("Running tests for DataAccess...\n");
	{
		std::unique_ptr<Container>           container(new Container);
		Node* entity = container->newAdd();
		std::unique_ptr<DataAccess> dataAccessComponent(new DataAccess);

		entity->setMember("name", "UnitTestEntity");
		//entity->addComponent("dataAccess", dataAccessComponent.get());

		entity->add("BOOL");
		entity->setMember("BOOL", false);

		entity->add("STRING");
		entity->setMember("STRING", "hello world!");

		entity->add("NUMBER");
		entity->setMember("NUMBER", double(3.14));

		//dataAccessComponent->update();
		//entity->removeComponent("dataAccess");
	}

	
	auto testParser = [](const std::string& testName, const std::string& expression, const std::string& resultExpected)->void {

		LOG_DEBUG("\n Running %s: \"%s\" \n", testName.c_str(), expression.c_str());

		auto container(new Container);
		auto expressionVariable(container->newVariable("expression"));
		expressionVariable->setValue(expression);

		auto parser(container->newParser(expressionVariable));

		parser->eval();

		auto resultVariable = container->getResultVariable();
		resultVariable->update();

		auto result = resultVariable->getValueAsString();

		LOG_DEBUG("\n %s expression: \"%s\" ", testName.c_str(), expression.c_str());

		if (result == resultExpected){
			s_testSucceedCount++;
			LOG_MESSAGE( OK );

		} else {
			LOG_MESSAGE( KO "\n");
			LOG_ERROR("Should return %s\n Result %s\n", resultExpected.c_str(), result.c_str());
		}
		LOG_DEBUG("\n");

		s_testCount++;

		delete container;

	};

	LOG_MESSAGE("Running tests for Parser...\n");
	{
		testParser("Parser 00", "5"                                            ,"5");
		testParser("Parser 01", "-5"                                           ,"-5");
		testParser("Parser 02", "2+3"                                          ,"5");
		testParser("Parser 03", "-5+4"                                         ,"-1");
		testParser("Parser 04", "-1+2*5-3/6"                                   ,"8.5");

		testParser("Parser 05", "-1*20"                                        ,"-20");
		testParser("Parser 06", "(1+4)"                                        ,"5");
		testParser("Parser 07", "(1)+(2)"                                      ,"3");
		testParser("Parser 08", "(1+2)*3"                                      ,"9");
		testParser("Parser 09", "2*(5+3)"                                      ,"16");

		testParser("Parser 10", "2+(5*3)"                                      ,"17");
		testParser("Parser 11", "2*(5+3)+2"                                    ,"18");
		testParser("Parser 12", "(2-(5+3))-2+(1+1)"                            ,"-6");
		testParser("Parser 13", "(2 - ( 5 + 3 ) - 2 ) + 9 / (1 - 0.54)"        ,"11.565217");
		testParser("Parser 14", "1/3"                                          ,"0.333333");
	}


	DisplayResults();

	return s_testSucceedCount == s_testCount;
}