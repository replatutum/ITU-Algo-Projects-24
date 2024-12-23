#include "tweet.h"
#include <chrono>

int main(){
  std::string inputFilePath = "./data/sizes/tweets50k.csv";
  // std::string outputFilePath = "./data/new.csv";

  std::vector<Tweet> tweets;
  tweets = readTweetsFromFile(inputFilePath);
  mergeSort(tweets, 0, tweets.size()-1, "tweetID");

  long long key = 1773335;
  
  const auto start{std::chrono::steady_clock::now()};
  int index = binarySearch(tweets, key, "tweetID");
  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};
  
  std::cout << "Time: " << elapsed_seconds.count() << " seconds" << std::endl;
  std::cout << "Index: " << index << std::endl;

  // writeTweetsToFile(outputFilePath, tweets);

  return EXIT_SUCCESS;
}
