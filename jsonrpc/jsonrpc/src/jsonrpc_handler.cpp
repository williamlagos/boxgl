/*
 *  JsonRpc-Cpp - JSON-RPC implementation.
 *  Copyright (C) 2008-2009 Sebastien Vincent <sebastien.vincent@cppextrem.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file jsonrpc_handler.cpp
 * \brief JSON-RPC server processor engine.
 * \author Sebastien Vincent
 */

#include "jsonrpc_handler.h"

namespace Json
{
  Parser::~Parser() {

  }

  std::string Parser::StringValue(JSONNODE* poNode, std::string strName) {
    JSONNODE_ITERATOR i = json_begin(poNode);
    std::string strValue = "";
    while (i != json_end(poNode)){
      if (i == JSON_NULL) {
        break;
      } else if (json_type(*i) == JSON_NODE) {
        StringValue(i,strName);
      }
      json_char *node_name = json_name(*i);
      if (strcmp(node_name, strName.c_str()) == 0) {
        json_char *node_value = json_as_string(*i);
        strValue = node_value;
        json_free(node_value);
      }
      json_free(node_name);
      ++i;
    }
    return strValue;
  }

  namespace Rpc
  {

    CallbackMethod::~CallbackMethod()
    {
    }

    Handler::Handler()
    {
      /* add a RPC method that list the actual RPC methods contained in the Handler */
      JSONNODE *root = json_new(JSON_NODE);
      json_push_back(root, json_new_a("description", "List the RPC methods available"));
      json_push_back(root, json_new_i("parameters", JSON_NULL));
      json_push_back(root, json_new_a("returns", "Object that contains description of all methods registered"));

      /*JSONNODE r;

      r["description"] = "List the RPC methods available";
      r["parameters"] = JSON_JSON_NULL;
      r["returns"] = "Object that contains description of all methods registered";*/

      AddMethod(new RpcMethod<Handler>(*this, &Handler::SystemDescribe, std::string("system.describe"), root));
      json_delete(root);
    }

    Handler::~Handler()
    {
      /* delete all objects from the list */
      for(std::list<CallbackMethod*>::const_iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        delete (*it);
      }
      m_methods.clear();
      //json_delete_all();
    }

    void Handler::AddMethod(CallbackMethod* method)
    {
      m_methods.push_back(method);
    }

    void Handler::DeleteMethod(const std::string& name)
    {
      /* do not delete system defined method */
      if(name == "system.describe")
      {
        return;
      }

      for(std::list<CallbackMethod*>::iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        if((*it)->GetName() == name)
        {
          delete (*it);
          m_methods.erase(it);
          break;
        }
      }
    }

    bool Handler::SystemDescribe(JSONNODE* msg, JSONNODE* response)
    {
      JSONNODE *methods = json_new(JSON_NODE);
      json_push_back(response, json_new_a("jsonrpc","2.0"));
      json_push_back(response, json_new_a("id",json_as_string(*json_find(msg,"id"))));


      /*JSONNODE methods;
      response["jsonrpc"] = "2.0";
      response["id"] = msg["id"];*/

      for(std::list<CallbackMethod*>::iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        std::string strTempName = (*it)->GetName();
        std::string strTempDescription = json_as_string(*json_find((*it)->GetDescription(),"description"));
        json_push_back(methods, json_new_a(strTempName.c_str(),strTempDescription.c_str()));
        //methods[(*it)->getName()] = (*it)->GetDescription();
      }
      
      json_set_name(response, "result");
      json_push_back(response, methods);
      //response["result"] = methods;
      json_delete(methods);
      return true;
    }

    std::string Handler::GetString(JSONNODE* value)
    {
      //m_writer.write(value);
      return json_as_string(value);
    }

    bool Handler::Check(JSONNODE* root, JSONNODE* error)
    {
      JSONNODE* err = json_new(JSON_NODE);
      bool bRetVal = true;
      
      /* check the JSON-RPC version => 2.0 */
      if(json_find(root,"jsonrpc") == JSON_NULL
        /*!root.isObject() || !root.isMember("jsonrpc") || root["jsonrpc"] != "2.0"*/) 
      {
        //if(strcmp(json_write(*json_find(root,"jsonrpc")),"2.0") != 0){
        json_push_back(error, json_new_a("jsonrpc",JSON_NULL));
        json_push_back(error, json_new_a("jsonrpc","2.0"));
  
        json_push_back(err, json_new_i("code",INVALID_REQUEST));
        json_push_back(err, json_new_a("jsonrpc","Invalid JSON-RPC request."));
        json_set_name(error,"error");
        json_push_back(error,err);

        /*error["id"] = JSON_NULL;
        error["jsonrpc"] = "2.0";
          
        err["code"] = INVALID_REQUEST;
        err["message"] = "Invalid JSON-RPC request.";
        error["error"] = err;*/
        
        bRetVal = false;
        //}
      }

      if(json_find(root,"id") == JSON_NULL
         /*root.isMember("id") && (root["id"].isArray() || root["id"].isObject())*/)
      {
        //if(json_type(*json_find(root,"id")) != JSON_ARRAY || json_type(*json_find(root,"id")) != JSON_NODE){
        json_push_back(error, json_new_a("jsonrpc",JSON_NULL));
        json_push_back(error, json_new_a("jsonrpc","2.0"));

        json_push_back(err, json_new_i("code",INVALID_REQUEST));
        json_push_back(err, json_new_a("jsonrpc","Invalid JSON-RPC request."));
        json_set_name(error,"error");
        json_push_back(error,err);

        /*error["id"] = JSON_NULL;
        error["jsonrpc"] = "2.0";

        err["code"] = INVALID_REQUEST;
        err["message"] = "Invalid JSON-RPC request.";
        error["error"] = err;*/
        bRetVal = false;
        //}
      }

      /* extract "method" attribute */
      if(json_find(root,"method") == JSON_NULL
        /*!root.isMember("method") || !root["method"].isString()*/)
      {
        //if(!json_as_string(*json_find(root,"method"))){
        json_push_back(error, json_new_a("jsonrpc",JSON_NULL));
        json_push_back(error, json_new_a("jsonrpc","2.0"));

        json_push_back(err, json_new_i("code",INVALID_REQUEST));
        json_push_back(err, json_new_a("jsonrpc","Invalid JSON-RPC request."));
        json_set_name(error,"error");
        json_push_back(error,err);

        /*error["id"] = JSON_NULL;
        error["jsonrpc"] = "2.0";

        err["code"] = INVALID_REQUEST;
        err["message"] = "Invalid JSON-RPC request.";
        error["error"] = err;*/
        bRetVal = false;
        //}
      }
      
      json_delete(err);

      return bRetVal;
    }

    bool Handler::Process(JSONNODE* root, JSONNODE* response)
    {
      JSONNODE* error = json_new(JSON_NODE);

      if(!Check(root, error))
      {
        response = error;
        return false;
      }

      std::string strMethod = m_Parser.StringValue(root,"method");

      //method = json_write(*json_find(root,"method"));
      
      if(strMethod != "")
      {
        CallbackMethod* rpc = Lookup(strMethod);
        if(rpc)
        {
          json_delete(error);
          return rpc->Call(root, response);
        }
      }
      
      /* forge an error response */
      json_push_back(response, json_new_a("jsonrpc",JSON_NULL));
      json_push_back(response, json_new_a("jsonrpc","2.0"));

      json_push_back(error, json_new_i("code",METHOD_NOT_FOUND));
      json_push_back(error, json_new_a("jsonrpc","Method not found."));
      json_set_name(response,"error");
      json_push_back(response,error);

      /*response["id"] = root.isMember("id") ? root["id"] : JSON_NULL;
      response["jsonrpc"] = "2.0";

      error["code"] = METHOD_NOT_FOUND;
      error["message"] = "Method not found.";
      response["error"] = error;*/

      json_delete(error);

      return false;
    }

    bool Handler::Process(const std::string& msg, JSONNODE* response)
    {
      JSONNODE* root = json_new(JSON_ARRAY);
      JSONNODE* error = json_new(JSON_NODE);
      bool bRetVal = true;
      /* parsing */

      using namespace std;

      if(msg.empty()) {
        json_delete(root);
        json_delete(error);
        return false;
      }

      vector<string> tokens;
      vector<string>::iterator it;

      string delim = "!!";
      size_t  start = 0, end = 0;
      while ( end != string::npos ){
        end = msg.find(delim,start);
        tokens.push_back(msg.substr(start,(end == string::npos) ? string::npos : end - start));
        start = ((end > (string::npos - delim.size())) ? string::npos : end + delim.size());
      }

      for (it = tokens.begin(); it != tokens.end(); it++) {
        std::string msgRoot = (*it);
        msgRoot = msgRoot+"\"}";
        root = json_parse_unformatted(json_strip_white_space(msgRoot.c_str()));
        std::string strRoot = json_write_formatted(root);
        
        if (root == JSON_NULL) {
          /* request or batched call is not in JSON format */
          json_push_back(response, json_new_a("jsonrpc",JSON_NULL));
          json_push_back(response, json_new_a("jsonrpc","2.0"));

          json_push_back(error, json_new_i("code",METHOD_NOT_FOUND));
          json_push_back(error, json_new_a("jsonrpc","Method not found."));
          json_set_name(response,"error");
          json_push_back(response,error);

          bRetVal = false;
        } else if(json_type(root) == JSON_ARRAY) {
          JSONNODE_ITERATOR it = json_begin(root);
          JSONNODE* ret = json_new(JSON_NODE);
          while(it != json_end(root)){
            Process(it,ret);
            if(ret != JSON_NULL)
            {
              json_push_back(response,json_new_a(NULL,json_as_string(ret)));
            }
          }
          json_delete(ret);
          json_delete(it);
          bRetVal = true;
        } else {
          bRetVal = Process(root,response);
        }
      }
      json_delete(root);
      json_delete(error);
      return bRetVal;

      //root = m_reader.parse(msg);

      /*if(root = Json::Value:null){
        response["id"] = JSON_JSON_NULL;
        response["jsonrpc"] = "2.0";
          
        error["code"] = PARSING_ERROR;
        error["message"] = "Parse error.";
        response["error"] = error; 
      }*/

      /*if(root.isArray())
      {
        // batched call 
        size_t i = 0;
        size_t j = 0;
        
        for(i = 0 ; i < root.size() ; i++)
        {
          Json::Value ret;
          Process(root[i], ret);
          
          if(ret != Json::Value::null)
          {
            // it is not a notification, add to array of responses
            response[j] = ret;
            j++;
          }
        }
        return true;
      }
      else
      {
        return Process(root, response);
      }*/
    }

    bool Handler::Process(const char* msg, JSONNODE* response)
    {
      std::string str(msg);

      return Process(str, response);
    }

    CallbackMethod* Handler::Lookup(const std::string& name) const
    {
      for(std::list<CallbackMethod*>::const_iterator it = m_methods.begin() ; it != m_methods.end() ; it++)
      {
        if((*it)->GetName() == name)
        {
          return (*it);
        }
      }

      return 0;
    }

  } /* namespace Rpc */

} /* namespace Json */

