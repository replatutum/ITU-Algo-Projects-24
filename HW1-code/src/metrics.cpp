#include "tweet.h"

// assuming from the test files that the input array is not sorted
int countAboveThreshold(const std::vector<Tweet>& tweets, const std::string& metric, int threshold) {
  int count = 0;

  if (metric == "tweetID"){
    for (size_t i = 0; i < tweets.size(); i++){
      if (tweets[i].tweetID > threshold){
        count++;
      }
    }
    
  } else if (metric == "retweetCount"){
    for (size_t i = 0; i < tweets.size(); i++){
      if (tweets[i].retweetCount > threshold){
        count++;
      }
    }
    
  } else if (metric == "favoriteCount"){
    for (size_t i = 0; i < tweets.size(); i++){
      if (tweets[i].favoriteCount > threshold){
        count++;
      }
    }
    
  } else{
    std::cerr << "Wrong metric for countAboveThreshold()" << std::endl;
    return -1;
  }

  return count;
}

// returns index !!!
int binarySearch(const std::vector<Tweet>& tweets, long long key, const std::string& sortBy){
  int left = 0, right = tweets.size() - 1;
  int mid;

  if (sortBy == "tweetID"){
    while (left <= right){
      mid = (right + left) / 2;

      if (key == tweets[mid].tweetID) {
        return mid;
      }
      
      if (key > tweets[mid].tweetID) {
        left = mid + 1;
      } else{
        right = mid - 1;
      }
    }

    // if key can't be found
    return -1;

  } else if (sortBy == "retweetCount"){
    while (left <= right){
      mid = (right + left) / 2;

      if (key == tweets[mid].retweetCount) {
        return mid;
      }
      
      if (key > tweets[mid].retweetCount) {
        left = mid + 1;
      } else{
        right = mid - 1;
      }
    }

    // if key can't be found
    return -1;
    
  } else if (sortBy == "favoriteCount"){
    while (left <= right){
      mid = (right + left) / 2;

      if (key == tweets[mid].favoriteCount) {
        return mid;
      }
      
      if (key > tweets[mid].favoriteCount) {
        left = mid + 1;
      } else{
        right = mid - 1;
      }
    }

    // if key can't be found
    return -1;
    
  } else{
    std::cerr << "Wrong metric for binarySearch()" << std::endl;
    return -1;
  }
}