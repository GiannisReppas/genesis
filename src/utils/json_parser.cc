/**
 * @brief Implementation of JSON Parser functions.
 *
 * @file
 * @ingroup utils
 */

#include "utils/json_parser.hh"

#include "utils/logging.hh"

namespace genesis {

// =============================================================================
//     Process
// =============================================================================

bool JsonParser::Process (const std::string& json, JsonDocument& document)
{
    JsonLexer lexer;
    lexer.Process(json);
    return Process(lexer, document);
}

bool JsonParser::Process (const JsonLexer& lexer, JsonDocument& document)
{
    if (lexer.empty()) {
        LOG_INFO << "JSON file is empty. Nothing done.";
        return false;
    }
    if (lexer.HasError()) {
        LOG_WARN << "Lexing error at " << lexer.back().at()
                 << " with message: " << lexer.back().value();
        return false;
    }
    if (!lexer.begin()->IsBracket("{")) {
        LOG_WARN << "JSON document does not start with JSON object opener '{'.";
        return false;
    }

    document.clear();
    Lexer::const_iterator begin = lexer.begin();
    Lexer::const_iterator end   = lexer.end();
    if (!ProcessObject(begin, end, &document)) {
        return false;
    }
    if (begin != end) {
        LOG_WARN << "JSON document contains more information after the closing bracket.";
        return false;
    }
    return true;
}

// =============================================================================
//     ProcessValue
// =============================================================================

bool JsonParser::ProcessValue (
    Lexer::const_iterator& ct,
    Lexer::const_iterator& end,
    JsonValue*&            value
) {
    if (ct->IsSymbol()) {
        // the lexer only returns null, true or false as symbols, so this is safe
        if (ct->value().compare("null") == 0) {
            value = new JsonValueNull();
        } else {
            value = new JsonValueBool(ct->value());
        }
        ++ct;
        return true;
    }
    if (ct->IsNumber()) {
        value = new JsonValueNumber(ct->value());
        ++ct;
        return true;
    }
    if (ct->IsString()) {
        value = new JsonValueString(ct->value());
        ++ct;
        return true;
    }
    if (ct->IsBracket("[")) {
        JsonValueArray* arr = new JsonValueArray();
        value = arr;
        return ProcessArray (ct, end, arr);
    }
    if (ct->IsBracket("{")) {
        JsonValueObject* obj = new JsonValueObject();
        value = obj;
        return ProcessObject (ct, end, obj);
    }

    LOG_WARN << "JSON value contains invalid characters at " + ct->at() + ": '" + ct->value() + "'.";
    return false;
}

// =============================================================================
//     ProcessArray
// =============================================================================

bool JsonParser::ProcessArray (
    Lexer::const_iterator& ct,
    Lexer::const_iterator& end,
    JsonValueArray*        value
) {
    if (!value) {
        value = new JsonValueArray();
    }

    if (ct == end || !ct->IsBracket("[")) {
        LOG_WARN << "JSON array does not start with '[' at " << ct->at() << ".";
        return false;
    }

    ++ct;
    while (ct != end) {
        // proccess the array element
        JsonValue* element = nullptr;
        if (!ProcessValue(ct, end, element)) {
            return false;
        }
        value->data.push_back(element);

        // check for end of array, leave if found
        if (ct == end || ct->IsBracket("]")) {
            break;
        }

        // check for delimiter comma (indicates that there are more elements following)
        if (!ct->IsOperator(",")) {
            LOG_WARN << "JSON array does not contain comma between elements at " << ct->at() << ".";
            return false;
        }
        ++ct;
    }

    if (ct == end) {
        LOG_WARN << "JSON array ended unexpectedly.";
        return false;
    }
    ++ct;
    return true;
}

// =============================================================================
//     ProcessObject
// =============================================================================

bool JsonParser::ProcessObject (
    Lexer::const_iterator& ct,
    Lexer::const_iterator& end,
    JsonValueObject*       value
) {
    if (!value) {
        value = new JsonValueObject();
    }

    if (ct == end || !ct->IsBracket("{")) {
        LOG_WARN << "JSON object does not start with '{' at " << ct->at() << ".";
        return false;
    }

    ++ct;
    while (ct != end) {
        // check for name string and store it
        if (!ct->IsString()) {
            LOG_WARN << "JSON object member does not start with name string at " << ct->at() << ".";
            return false;
        }
        std::string name = ct->value();
        ++ct;

        // check for delimiter colon
        if (ct == end) {
            break;
        }
        if (!ct->IsOperator(":")) {
            LOG_WARN << "JSON object member does not contain colon between name and value at "
                     << ct->at() << ".";
            return false;
        }
        ++ct;

        // check for value and store it
        if (ct == end) {
            break;
        }
        JsonValue* member = nullptr;
        if (!ProcessValue(ct, end, member)) {
            return false;
        }
        value->Set(name, member);

        // check for end of object, leave if found
        if (ct == end || ct->IsBracket("}")) {
            break;
        }

        // check for delimiter comma (indicates that there are more members following)
        if (!ct->IsOperator(",")) {
            LOG_WARN << "JSON object does not contain comma between members at " << ct->at() << ".";
            return false;
        }
        ++ct;
    }

    if (ct == end) {
        LOG_WARN << "JSON object ended unexpectedly.";
        return false;
    }
    ++ct;
    return true;
}

}
