#include "GameRequestHandler.h"
#include "Helper.h"
#include "json.hpp"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "GameManager.h"

/*
* The Constructor of Class GameRequestHandler
* input: factory - the factory handler (RequestHandlerFactory&)
*		,user - the user logged in (LoggedUser&)
*		,game - the game of which the user is in (Game&)
* output: none
*/
GameRequestHandler::GameRequestHandler(RequestHandlerFactory& factory, LoggedUser& user, Game& game) :
	IRequestHandler(), m_handlerFactory(factory), m_gameManager(factory.getGameManager()), m_user(user), m_game(game)
{
}

/*
* The Distructor of Class GameRequestHandler
* input: none
* output: none
*/
GameRequestHandler::~GameRequestHandler()
{
}

/*
* check if the request is part of the game requests
* input: info - the request information (RequestInfo)
* output: isRequestRelevent - if the request is part of the game requests (bool)
*/
bool GameRequestHandler::isRequestRelevent(RequestInfo info)
{
	return info.id == RequestId::MT_GET_QUESTION|| info.id == RequestId::MT_SUBMIT_ANSWER || info.id == RequestId::MT_GET_GAME_RESULT || info.id == RequestId::MT_LEAVE_GAME;
}

/*
* handle the game requests from the client
* input: info - the request information (RequestInfo)
* output: requestRes - the request result to send back to client (RequestResult)
*/
RequestResult GameRequestHandler::RequestHandler(RequestInfo info)
{
	if (!isRequestRelevent(info))
	{
		std::string message = "Error!....Wait for start or leave Room to continue";
		return error(message);
	}

	try
	{
		switch (info.id)
		{
		case RequestId::MT_GET_QUESTION:
			return getQuestion(info);
		case RequestId::MT_SUBMIT_ANSWER:
			return submitAnswer(info);
		case RequestId::MT_GET_GAME_RESULT:
			return getGameResults(info);
		case RequestId::MT_LEAVE_GAME:
			return leaveGame(info);
		}
	}
	catch (nlohmann::json::parse_error& e)
	{
		std::string message = "Error!....Invalid Json";
		return error(message);
	}
	catch (ExceptionHandler& e)
	{
		std::string message = e.what();
		std::cout << message << std::endl;
		return error(message);
	}
}

/*
* the function handles the getQuestion requests of the user
* input: info - the getQuestion request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	Question question = m_game.getQuestionForUser(m_user);
	int status = MT_RESPONSE_OK;
	if (question.getQuestion() == "")
	{
		status = MT_ERROR; //out of question
	}
	std::cout << m_user.getUsername() << " has asked for a question!" << std::endl;
	GetQuestionResponse qRes = { status, question.getQuestion(),  question.getCorrectAnswer(), question.getPossibleAnswers() };
	buffer = JsonResponseSerializer::serializeGetQuestionResponse(qRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the submitAnswer requests of the user
* input: info - the submitAnswer request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	SubmitAnswerRequest submitReq = JsonRequestPacketDeserializer::deserializerSubmitAnswerRequest(info.buffer);
	std::cout << m_user.getUsername() << " has submited an answer!" << std::endl;
	m_gameManager.submitAnswer(m_game, m_user, submitReq.answer ,submitReq.answerTime);
	SubmitAnswerResponse submitRes = { MT_RESPONSE_OK };
	buffer = JsonResponseSerializer::serializeSubmitAnswerResponse(submitRes);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the getGameResults requests of the user
* input: info - the getGameResults request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	GetGameResultsResponse gameRes = { MT_RESPONSE_OK,  m_gameManager.getGameResults(m_game)};
	std::cout << m_game.getGameId() << " has ended...Now Showing scores" << std::endl;
	buffer = JsonResponseSerializer::serializeGetGameResultsResponse(gameRes);
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}

/*
* the function handles the leaveGame requests of the user
* input: info - the leaveGame request of the user (RequestInfo)
* output: requestRes - the response to send to the user (RequestResult)
*/
RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler = nullptr;
	m_game.removePlayer(m_user);
	std::cout << m_user.getUsername() << " has left game " << m_game.getGameId() << std::endl;
	LeaveGameResponse leaveGameRes = { MT_RESPONSE_OK};
	buffer = JsonResponseSerializer::serializeLeaveGameResponse(leaveGameRes);
	newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	RequestResult requestRes = { buffer, newHandler };
	return requestRes;
}