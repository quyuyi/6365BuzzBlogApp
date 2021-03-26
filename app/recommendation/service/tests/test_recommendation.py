# Copyright (C) 2020 Georgia Tech Center for Experimental Research in Computer
# Systems

import time
import unittest

from buzzblog.gen.ttypes import *
from buzzblog.recommendation_client import Client as RecommendationClient


IP_ADDRESS = "localhost"
PORT = 9096


class TestService(unittest.TestCase):
  def test_retrieve_recommended_posts(self):
    with RecommendationClient(IP_ADDRESS, PORT) as client:
      # Retrieve posts with keyword "hello"
      rec_posts = client.retrieve_recommended_posts("hello")
      for p in rec_posts:
        print(p)


if __name__ == "__main__":
  unittest.main()