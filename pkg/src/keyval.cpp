//Copyright 2013 Revolution Analytics
//   
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS, 
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include "keyval.h"
#include <vector>
#include <Rcpp.h>

using namespace Rcpp;

SEXP null_purge(SEXP xx) {
  List _xx(xx);
  int n = _xx.size();
  int not_null_count = 0;
  for (int i = 0; i < n; i ++) 
    if (!Rf_isNull(_xx[i])) not_null_count++;
  List yy(not_null_count);
  for (int i = 0, j = 0; i < n; i ++) 
    if (!Rf_isNull(_xx[i])){
      yy[j] = _xx[i];
      j++;}
  return wrap(yy);}

SEXP lapply_as_character(SEXP xx) {
  List _xx(xx);
  List yy(_xx.size());
  for (int i = 0; i < _xx.size(); i ++) 
    yy[i] = Rf_asCharacterFactor(_xx[i]);
  return wrap(yy);}
  
int rmr_length(SEXP x) {
  if(Rf_isMatrix(x))
      return Rf_nrows(x);
  RObject _x(x);
  if (_x.hasAttribute("class")) {
    if(as<std::string>(_x.attr("class")) == "data.frame") {
      List __x(x);
      if(Rf_length(__x) == 0) {
        return(0);}
      else {
        return(Rf_length(__x[0]));}}}
  return Rf_length(x);}

SEXP sapply_rmr_length(SEXP xx) {
  List _xx(xx);
  std::vector<int> results(_xx.size());
  for(unsigned int i = 0; i < _xx.size(); i++) {
    results[i] = rmr_length(_xx[i]);}
  return(wrap(results));}
  
SEXP sapply_rmr_length_lossy_data_frame(SEXP xx){
  List _xx(xx);
  std::vector<int> results(_xx.size());
  for(unsigned int i = 0; i < _xx.size(); i++) {
    List cols(as<List>(_xx[i]));
    results[i] = rmr_length(cols[0]);}
  return wrap(results);}

int length_keyval(SEXP kv) {
  List kv_(kv);
  int kl = rmr_length(kv_["key"]);
  int vl = rmr_length(kv_["val"]);
  if (kl > vl) return(kl);
  return(vl);}
  
SEXP sapply_length_keyval(SEXP kvs) {
  List _kvs(kvs);
  std::vector<int> results(_kvs.size());
  for(unsigned int i = 0; i < _kvs.size(); i++) {
    results[i] = length_keyval(_kvs[i]);}
  return(wrap(results));}

SEXP sapply_null_keys(SEXP kvs) {
  List _kvs(kvs);
  std::vector<bool> results(_kvs.size());
  for(unsigned int i = 0; i < _kvs.size(); i++) {
    List kv(wrap(_kvs[i]));
    results[i] = Rf_isNull(kv["key"]);}
  return(wrap(results));}

SEXP sapply_is_list(SEXP l) {
  List _l(l);
  std::vector<bool> results(_l.size());
  for(unsigned int i = 0; i < _l.size(); i++) {
    results[i] = (as<RObject>(_l[i]).sexp_type() == VECSXP);}
  return wrap(results);}

SEXP lapply_key_val(SEXP kvs, std::string slot) {
  List _kvs(kvs);
  List results(_kvs.size());
  for(unsigned int i = 0; i < _kvs.size(); i++) {
    List kv(wrap(_kvs[i]));
    results[i] = kv[slot];}
  return wrap(results);}

SEXP lapply_keys(SEXP kvs) {
  return lapply_key_val(kvs, "key");}

SEXP lapply_values(SEXP kvs) {
  return lapply_key_val(kvs, "val");}

SEXP are_factor(SEXP xx) {
  List _xx(xx);
  std::vector<bool> results(_xx.size());
  for(unsigned int i = 0; i < _xx.size(); i++) {
    results[i] = Rf_isFactor(_xx[i]);}
  return wrap(results);}

bool is_data_frame(SEXP x) {
  RObject _x(x);
  if (_x.hasAttribute("class")) {
    if(as<std::string>(_x.attr("class")) == "data.frame") {
      return true;}}
  return false;}
  
SEXP are_data_frame(SEXP xx) {
  List _xx(xx);
    std::vector<bool> results(_xx.size());
  for(unsigned int i = 0; i < _xx.size(); i++) {
    results[i] = is_data_frame(_xx[i]);}
  return wrap(results);}
  
SEXP are_matrix(SEXP xx) {
  List _xx(xx);
    std::vector<bool> results(_xx.size());
  for(unsigned int i = 0; i < _xx.size(); i++) {
    results[i] = Rf_isMatrix(_xx[i]);}
  return wrap(results);}