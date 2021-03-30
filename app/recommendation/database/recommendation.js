// ref: https://docs.mongodb.com/manual/tutorial/write-scripts-for-the-mongo-shell/
// how to run: mongo localhost:<27017 or 5436> ./app/recommendation/database/recommendation.js

// connect to the database and collection
conn = new Mongo("localhost:5436");
db = conn.getDB("myDatabase");
collection = db.recommendations;

// insert into the collection
// TODO: change to your directory name
load('/home/quyuyi/Projects/6365BuzzBlogApp/app/recommendation/database/dataset.js');
collection.insertMany(dataset);

// create index on keywords
collection.createIndex({keywords:1});

// print query results: all documents in the collection
// cursor = collection.find();
// while ( cursor.hasNext() ) {
//    printjson( cursor.next() );
// }