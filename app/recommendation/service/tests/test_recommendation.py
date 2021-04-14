# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

import time
import unittest

from buzzblog.gen.ttypes import *
from buzzblog.recommendation_client import Client as RecommendationClient


IP_ADDRESS = "0.0.0.0"
PORT = 9096


class TestService(unittest.TestCase):
  def test_retrieve_recommended_posts(self):
    with RecommendationClient(IP_ADDRESS, PORT) as client:
      # Retrieve posts with keyword "hello"
      search_size = 10
      return_size = 5
      rec_posts = client.retrieve_recommended_posts("get", 10, 20)
      print(len(rec_posts))
      for p in rec_posts:
        print(p)


if __name__ == "__main__":
  unittest.main()
