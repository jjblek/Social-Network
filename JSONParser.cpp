//
// Created by Justin on 9/16/2022.
//

#include "JSONParser.hpp"
// CONSTRUCTOR
JSONParser::JSONParser(const std::string& nameOfInputFile):
    _tokenizer(nameOfInputFile)
{}

// parse JSONPair name/value pair (name : value)
JSONPair JSONParser::parseJSONData() {

    // initialize a JSONToken and populate it from JSONTokenizer
    JSONToken token = _tokenizer.getToken();

    // the first token is expected to be a quotation mark
    assert(token.isString());

    // initialize string 'first' with string token
    std::string first = token.getString();

    // the next token is expected to be a colon
    token = _tokenizer.getToken();
    assert(token.isColon());

    // the next token is expected to be an attribute value
    token = _tokenizer.getToken();

    // if the token is a quotation mark
    if (token.isString()) {

        // initialize a string 'second' with JSONToken::getString
        const std::string& second = token.getString();

        // initialize and return a pair of strings 'first' and 'second'
        JSONPair pair(first, second);

        return pair;
    }

    // else if the token is an array
    else if (token.isArray()) {

        // initialize a vector 'second' with JSONToken::getArray()
        const std::vector<std::string>& second = token.getArray();

        // initialize and return a pair of string 'first' and array 'second'
        JSONPair pair(first, second);

        return pair;
    }

    // else if the token is a number
    else if (token.isNumber()) {

        // initialize a double with JSONToken::getAttributeValue
        double second = token.getNumber();

        // initialize and return a pair of string 'first' and double 'second'
        JSONPair pair(first, second);

        return pair;
    }

    else { // else an unexpected character was found, exit with an error
        assert(token.isUnknown());
        exit(1);
    }
}

// parseJSONObject is responsible for parsing a JSONObject
JSONObject JSONParser::parseJSONObject() {

    JSONToken token = _tokenizer.getToken();

    // the first token is expected to be an open brace
    assert(token.isOpenBrace());

    JSONObject object;

    do { // parse JSONPairs
        JSONPair pair = parseJSONData();
        object.addPair(pair);
        token = _tokenizer.getToken();
    } while (token.isComma());

    // the last token is expected to be a closed brace
    assert(token.isClosedBrace());
    return object;
}

JSONEntity JSONParser::parseJSONEntity() {

    JSONEntity entity;

    // tokenize the first character
    JSONToken token = _tokenizer.getToken();

    // the first token is expected to be a string
    assert(token.isString());

    // set entity name
    entity.setEntityName(token.getString());

    // the next token is expected to be a colon
    token = _tokenizer.getToken();
    assert(token.isColon());

    // the next token is expected to be an open bracket ( [ )
    token = _tokenizer.getToken();
    assert(token.isOpenBracket());

    // comma separated JSON objects are expected within the brackets
    do { // parse JSONObjects
        JSONObject object = parseJSONObject();
        entity.addObject(object);
        token = _tokenizer.getToken();
    } while (token.isComma());

    // the last token is expected to be a closed bracket ( ] )
    assert(token.isClosedBracket());

    return entity;
}

JSONEntitySet JSONParser::parseJSONEntitySet() {

    JSONToken token = _tokenizer.getToken();

    // the first token is expected to be an open brace ( { )
    assert(token.isOpenBrace());

    JSONEntitySet set;

    do { // parse JSONEntities
        JSONEntity entity = parseJSONEntity();
        set.addEntity(entity);
        token = _tokenizer.getToken();
    } while (token.isComma());

    // the last token is expected to be a closed brace ( } )
    assert(token.isClosedBrace());

    return set;
}
