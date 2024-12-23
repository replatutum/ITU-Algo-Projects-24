#include "tweet.h"

std::vector<Tweet> readTweetsFromFile(const std::string& filename) {
  std::vector<Tweet> tweets;
  std::ifstream file(filename);

  if(!file.is_open()){
    std::cerr << "File could not be opened" << std::endl;
  }

  std::string line;
  std::getline(file, line);     // Ignore header

  while (std::getline(file, line)){
    Tweet tweet;
    int pos = 0;

    pos = line.find(',');
    tweet.tweetID = std::stoll(line.substr(0, pos));
    line.erase(0, pos + 1);

    pos = line.find(',');
    tweet.retweetCount = std::stoi(line.substr(0, pos));
    line.erase(0, pos + 1);

    tweet.favoriteCount = std::stoi(line);

    tweets.push_back(tweet);
  }

  file.close();
  return tweets;
}

void writeTweetsToFile(const std::string& filename, const std::vector<Tweet>& tweets) {
  FILE* file = fopen(filename.c_str(), "w");

  if (file == nullptr){
    std::cerr << "File could not be opened" << std::endl;
  }

  fprintf(file, "tweetID,retweet_count,favorite_count\n");      // Write header

  for (size_t i = 0; i < tweets.size(); i++){
    fprintf(file, "%lld,%d,%d\n", tweets[i].tweetID, tweets[i].retweetCount, tweets[i].favoriteCount);
  }

  fclose(file);
}