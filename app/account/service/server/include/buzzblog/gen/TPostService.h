/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TPostService_H
#define TPostService_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "buzzblog_types.h"

namespace gen {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class TPostServiceIf {
 public:
  virtual ~TPostServiceIf() {}
  virtual void create_post(TPost& _return, const int32_t requester_id, const std::string& text) = 0;
  virtual void retrieve_standard_post(TPost& _return, const int32_t requester_id, const int32_t post_id) = 0;
  virtual void retrieve_expanded_post(TPost& _return, const int32_t requester_id, const int32_t post_id) = 0;
  virtual void delete_post(const int32_t requester_id, const int32_t post_id) = 0;
  virtual void list_posts(std::vector<TPost> & _return, const int32_t requester_id, const int32_t author_id) = 0;
  virtual int32_t count_posts_by_author(const int32_t requester_id, const int32_t author_id) = 0;
};

class TPostServiceIfFactory {
 public:
  typedef TPostServiceIf Handler;

  virtual ~TPostServiceIfFactory() {}

  virtual TPostServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(TPostServiceIf* /* handler */) = 0;
};

class TPostServiceIfSingletonFactory : virtual public TPostServiceIfFactory {
 public:
  TPostServiceIfSingletonFactory(const ::std::shared_ptr<TPostServiceIf>& iface) : iface_(iface) {}
  virtual ~TPostServiceIfSingletonFactory() {}

  virtual TPostServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(TPostServiceIf* /* handler */) {}

 protected:
  ::std::shared_ptr<TPostServiceIf> iface_;
};

class TPostServiceNull : virtual public TPostServiceIf {
 public:
  virtual ~TPostServiceNull() {}
  void create_post(TPost& /* _return */, const int32_t /* requester_id */, const std::string& /* text */) {
    return;
  }
  void retrieve_standard_post(TPost& /* _return */, const int32_t /* requester_id */, const int32_t /* post_id */) {
    return;
  }
  void retrieve_expanded_post(TPost& /* _return */, const int32_t /* requester_id */, const int32_t /* post_id */) {
    return;
  }
  void delete_post(const int32_t /* requester_id */, const int32_t /* post_id */) {
    return;
  }
  void list_posts(std::vector<TPost> & /* _return */, const int32_t /* requester_id */, const int32_t /* author_id */) {
    return;
  }
  int32_t count_posts_by_author(const int32_t /* requester_id */, const int32_t /* author_id */) {
    int32_t _return = 0;
    return _return;
  }
};

typedef struct _TPostService_create_post_args__isset {
  _TPostService_create_post_args__isset() : requester_id(false), text(false) {}
  bool requester_id :1;
  bool text :1;
} _TPostService_create_post_args__isset;

class TPostService_create_post_args {
 public:

  TPostService_create_post_args(const TPostService_create_post_args&);
  TPostService_create_post_args& operator=(const TPostService_create_post_args&);
  TPostService_create_post_args() : requester_id(0), text() {
  }

  virtual ~TPostService_create_post_args() noexcept;
  int32_t requester_id;
  std::string text;

  _TPostService_create_post_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_text(const std::string& val);

  bool operator == (const TPostService_create_post_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(text == rhs.text))
      return false;
    return true;
  }
  bool operator != (const TPostService_create_post_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_create_post_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_create_post_pargs {
 public:


  virtual ~TPostService_create_post_pargs() noexcept;
  const int32_t* requester_id;
  const std::string* text;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_create_post_result__isset {
  _TPostService_create_post_result__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_create_post_result__isset;

class TPostService_create_post_result {
 public:

  TPostService_create_post_result(const TPostService_create_post_result&);
  TPostService_create_post_result& operator=(const TPostService_create_post_result&);
  TPostService_create_post_result() {
  }

  virtual ~TPostService_create_post_result() noexcept;
  TPost success;
  TPostInvalidAttributesException e;

  _TPostService_create_post_result__isset __isset;

  void __set_success(const TPost& val);

  void __set_e(const TPostInvalidAttributesException& val);

  bool operator == (const TPostService_create_post_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(e == rhs.e))
      return false;
    return true;
  }
  bool operator != (const TPostService_create_post_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_create_post_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_create_post_presult__isset {
  _TPostService_create_post_presult__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_create_post_presult__isset;

class TPostService_create_post_presult {
 public:


  virtual ~TPostService_create_post_presult() noexcept;
  TPost* success;
  TPostInvalidAttributesException e;

  _TPostService_create_post_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TPostService_retrieve_standard_post_args__isset {
  _TPostService_retrieve_standard_post_args__isset() : requester_id(false), post_id(false) {}
  bool requester_id :1;
  bool post_id :1;
} _TPostService_retrieve_standard_post_args__isset;

class TPostService_retrieve_standard_post_args {
 public:

  TPostService_retrieve_standard_post_args(const TPostService_retrieve_standard_post_args&);
  TPostService_retrieve_standard_post_args& operator=(const TPostService_retrieve_standard_post_args&);
  TPostService_retrieve_standard_post_args() : requester_id(0), post_id(0) {
  }

  virtual ~TPostService_retrieve_standard_post_args() noexcept;
  int32_t requester_id;
  int32_t post_id;

  _TPostService_retrieve_standard_post_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_post_id(const int32_t val);

  bool operator == (const TPostService_retrieve_standard_post_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(post_id == rhs.post_id))
      return false;
    return true;
  }
  bool operator != (const TPostService_retrieve_standard_post_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_retrieve_standard_post_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_retrieve_standard_post_pargs {
 public:


  virtual ~TPostService_retrieve_standard_post_pargs() noexcept;
  const int32_t* requester_id;
  const int32_t* post_id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_retrieve_standard_post_result__isset {
  _TPostService_retrieve_standard_post_result__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_retrieve_standard_post_result__isset;

class TPostService_retrieve_standard_post_result {
 public:

  TPostService_retrieve_standard_post_result(const TPostService_retrieve_standard_post_result&);
  TPostService_retrieve_standard_post_result& operator=(const TPostService_retrieve_standard_post_result&);
  TPostService_retrieve_standard_post_result() {
  }

  virtual ~TPostService_retrieve_standard_post_result() noexcept;
  TPost success;
  TPostNotFoundException e;

  _TPostService_retrieve_standard_post_result__isset __isset;

  void __set_success(const TPost& val);

  void __set_e(const TPostNotFoundException& val);

  bool operator == (const TPostService_retrieve_standard_post_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(e == rhs.e))
      return false;
    return true;
  }
  bool operator != (const TPostService_retrieve_standard_post_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_retrieve_standard_post_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_retrieve_standard_post_presult__isset {
  _TPostService_retrieve_standard_post_presult__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_retrieve_standard_post_presult__isset;

class TPostService_retrieve_standard_post_presult {
 public:


  virtual ~TPostService_retrieve_standard_post_presult() noexcept;
  TPost* success;
  TPostNotFoundException e;

  _TPostService_retrieve_standard_post_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TPostService_retrieve_expanded_post_args__isset {
  _TPostService_retrieve_expanded_post_args__isset() : requester_id(false), post_id(false) {}
  bool requester_id :1;
  bool post_id :1;
} _TPostService_retrieve_expanded_post_args__isset;

class TPostService_retrieve_expanded_post_args {
 public:

  TPostService_retrieve_expanded_post_args(const TPostService_retrieve_expanded_post_args&);
  TPostService_retrieve_expanded_post_args& operator=(const TPostService_retrieve_expanded_post_args&);
  TPostService_retrieve_expanded_post_args() : requester_id(0), post_id(0) {
  }

  virtual ~TPostService_retrieve_expanded_post_args() noexcept;
  int32_t requester_id;
  int32_t post_id;

  _TPostService_retrieve_expanded_post_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_post_id(const int32_t val);

  bool operator == (const TPostService_retrieve_expanded_post_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(post_id == rhs.post_id))
      return false;
    return true;
  }
  bool operator != (const TPostService_retrieve_expanded_post_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_retrieve_expanded_post_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_retrieve_expanded_post_pargs {
 public:


  virtual ~TPostService_retrieve_expanded_post_pargs() noexcept;
  const int32_t* requester_id;
  const int32_t* post_id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_retrieve_expanded_post_result__isset {
  _TPostService_retrieve_expanded_post_result__isset() : success(false), e1(false), e2(false) {}
  bool success :1;
  bool e1 :1;
  bool e2 :1;
} _TPostService_retrieve_expanded_post_result__isset;

class TPostService_retrieve_expanded_post_result {
 public:

  TPostService_retrieve_expanded_post_result(const TPostService_retrieve_expanded_post_result&);
  TPostService_retrieve_expanded_post_result& operator=(const TPostService_retrieve_expanded_post_result&);
  TPostService_retrieve_expanded_post_result() {
  }

  virtual ~TPostService_retrieve_expanded_post_result() noexcept;
  TPost success;
  TPostNotFoundException e1;
  TAccountNotFoundException e2;

  _TPostService_retrieve_expanded_post_result__isset __isset;

  void __set_success(const TPost& val);

  void __set_e1(const TPostNotFoundException& val);

  void __set_e2(const TAccountNotFoundException& val);

  bool operator == (const TPostService_retrieve_expanded_post_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(e1 == rhs.e1))
      return false;
    if (!(e2 == rhs.e2))
      return false;
    return true;
  }
  bool operator != (const TPostService_retrieve_expanded_post_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_retrieve_expanded_post_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_retrieve_expanded_post_presult__isset {
  _TPostService_retrieve_expanded_post_presult__isset() : success(false), e1(false), e2(false) {}
  bool success :1;
  bool e1 :1;
  bool e2 :1;
} _TPostService_retrieve_expanded_post_presult__isset;

class TPostService_retrieve_expanded_post_presult {
 public:


  virtual ~TPostService_retrieve_expanded_post_presult() noexcept;
  TPost* success;
  TPostNotFoundException e1;
  TAccountNotFoundException e2;

  _TPostService_retrieve_expanded_post_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TPostService_delete_post_args__isset {
  _TPostService_delete_post_args__isset() : requester_id(false), post_id(false) {}
  bool requester_id :1;
  bool post_id :1;
} _TPostService_delete_post_args__isset;

class TPostService_delete_post_args {
 public:

  TPostService_delete_post_args(const TPostService_delete_post_args&);
  TPostService_delete_post_args& operator=(const TPostService_delete_post_args&);
  TPostService_delete_post_args() : requester_id(0), post_id(0) {
  }

  virtual ~TPostService_delete_post_args() noexcept;
  int32_t requester_id;
  int32_t post_id;

  _TPostService_delete_post_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_post_id(const int32_t val);

  bool operator == (const TPostService_delete_post_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(post_id == rhs.post_id))
      return false;
    return true;
  }
  bool operator != (const TPostService_delete_post_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_delete_post_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_delete_post_pargs {
 public:


  virtual ~TPostService_delete_post_pargs() noexcept;
  const int32_t* requester_id;
  const int32_t* post_id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_delete_post_result__isset {
  _TPostService_delete_post_result__isset() : e1(false), e2(false) {}
  bool e1 :1;
  bool e2 :1;
} _TPostService_delete_post_result__isset;

class TPostService_delete_post_result {
 public:

  TPostService_delete_post_result(const TPostService_delete_post_result&);
  TPostService_delete_post_result& operator=(const TPostService_delete_post_result&);
  TPostService_delete_post_result() {
  }

  virtual ~TPostService_delete_post_result() noexcept;
  TPostNotFoundException e1;
  TPostNotAuthorizedException e2;

  _TPostService_delete_post_result__isset __isset;

  void __set_e1(const TPostNotFoundException& val);

  void __set_e2(const TPostNotAuthorizedException& val);

  bool operator == (const TPostService_delete_post_result & rhs) const
  {
    if (!(e1 == rhs.e1))
      return false;
    if (!(e2 == rhs.e2))
      return false;
    return true;
  }
  bool operator != (const TPostService_delete_post_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_delete_post_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_delete_post_presult__isset {
  _TPostService_delete_post_presult__isset() : e1(false), e2(false) {}
  bool e1 :1;
  bool e2 :1;
} _TPostService_delete_post_presult__isset;

class TPostService_delete_post_presult {
 public:


  virtual ~TPostService_delete_post_presult() noexcept;
  TPostNotFoundException e1;
  TPostNotAuthorizedException e2;

  _TPostService_delete_post_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TPostService_list_posts_args__isset {
  _TPostService_list_posts_args__isset() : requester_id(false), author_id(false) {}
  bool requester_id :1;
  bool author_id :1;
} _TPostService_list_posts_args__isset;

class TPostService_list_posts_args {
 public:

  TPostService_list_posts_args(const TPostService_list_posts_args&);
  TPostService_list_posts_args& operator=(const TPostService_list_posts_args&);
  TPostService_list_posts_args() : requester_id(0), author_id(0) {
  }

  virtual ~TPostService_list_posts_args() noexcept;
  int32_t requester_id;
  int32_t author_id;

  _TPostService_list_posts_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_author_id(const int32_t val);

  bool operator == (const TPostService_list_posts_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(author_id == rhs.author_id))
      return false;
    return true;
  }
  bool operator != (const TPostService_list_posts_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_list_posts_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_list_posts_pargs {
 public:


  virtual ~TPostService_list_posts_pargs() noexcept;
  const int32_t* requester_id;
  const int32_t* author_id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_list_posts_result__isset {
  _TPostService_list_posts_result__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_list_posts_result__isset;

class TPostService_list_posts_result {
 public:

  TPostService_list_posts_result(const TPostService_list_posts_result&);
  TPostService_list_posts_result& operator=(const TPostService_list_posts_result&);
  TPostService_list_posts_result() {
  }

  virtual ~TPostService_list_posts_result() noexcept;
  std::vector<TPost>  success;
  TAccountNotFoundException e;

  _TPostService_list_posts_result__isset __isset;

  void __set_success(const std::vector<TPost> & val);

  void __set_e(const TAccountNotFoundException& val);

  bool operator == (const TPostService_list_posts_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(e == rhs.e))
      return false;
    return true;
  }
  bool operator != (const TPostService_list_posts_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_list_posts_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_list_posts_presult__isset {
  _TPostService_list_posts_presult__isset() : success(false), e(false) {}
  bool success :1;
  bool e :1;
} _TPostService_list_posts_presult__isset;

class TPostService_list_posts_presult {
 public:


  virtual ~TPostService_list_posts_presult() noexcept;
  std::vector<TPost> * success;
  TAccountNotFoundException e;

  _TPostService_list_posts_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _TPostService_count_posts_by_author_args__isset {
  _TPostService_count_posts_by_author_args__isset() : requester_id(false), author_id(false) {}
  bool requester_id :1;
  bool author_id :1;
} _TPostService_count_posts_by_author_args__isset;

class TPostService_count_posts_by_author_args {
 public:

  TPostService_count_posts_by_author_args(const TPostService_count_posts_by_author_args&);
  TPostService_count_posts_by_author_args& operator=(const TPostService_count_posts_by_author_args&);
  TPostService_count_posts_by_author_args() : requester_id(0), author_id(0) {
  }

  virtual ~TPostService_count_posts_by_author_args() noexcept;
  int32_t requester_id;
  int32_t author_id;

  _TPostService_count_posts_by_author_args__isset __isset;

  void __set_requester_id(const int32_t val);

  void __set_author_id(const int32_t val);

  bool operator == (const TPostService_count_posts_by_author_args & rhs) const
  {
    if (!(requester_id == rhs.requester_id))
      return false;
    if (!(author_id == rhs.author_id))
      return false;
    return true;
  }
  bool operator != (const TPostService_count_posts_by_author_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_count_posts_by_author_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class TPostService_count_posts_by_author_pargs {
 public:


  virtual ~TPostService_count_posts_by_author_pargs() noexcept;
  const int32_t* requester_id;
  const int32_t* author_id;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_count_posts_by_author_result__isset {
  _TPostService_count_posts_by_author_result__isset() : success(false) {}
  bool success :1;
} _TPostService_count_posts_by_author_result__isset;

class TPostService_count_posts_by_author_result {
 public:

  TPostService_count_posts_by_author_result(const TPostService_count_posts_by_author_result&);
  TPostService_count_posts_by_author_result& operator=(const TPostService_count_posts_by_author_result&);
  TPostService_count_posts_by_author_result() : success(0) {
  }

  virtual ~TPostService_count_posts_by_author_result() noexcept;
  int32_t success;

  _TPostService_count_posts_by_author_result__isset __isset;

  void __set_success(const int32_t val);

  bool operator == (const TPostService_count_posts_by_author_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const TPostService_count_posts_by_author_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TPostService_count_posts_by_author_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _TPostService_count_posts_by_author_presult__isset {
  _TPostService_count_posts_by_author_presult__isset() : success(false) {}
  bool success :1;
} _TPostService_count_posts_by_author_presult__isset;

class TPostService_count_posts_by_author_presult {
 public:


  virtual ~TPostService_count_posts_by_author_presult() noexcept;
  int32_t* success;

  _TPostService_count_posts_by_author_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class TPostServiceClient : virtual public TPostServiceIf {
 public:
  TPostServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  TPostServiceClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void create_post(TPost& _return, const int32_t requester_id, const std::string& text);
  void send_create_post(const int32_t requester_id, const std::string& text);
  void recv_create_post(TPost& _return);
  void retrieve_standard_post(TPost& _return, const int32_t requester_id, const int32_t post_id);
  void send_retrieve_standard_post(const int32_t requester_id, const int32_t post_id);
  void recv_retrieve_standard_post(TPost& _return);
  void retrieve_expanded_post(TPost& _return, const int32_t requester_id, const int32_t post_id);
  void send_retrieve_expanded_post(const int32_t requester_id, const int32_t post_id);
  void recv_retrieve_expanded_post(TPost& _return);
  void delete_post(const int32_t requester_id, const int32_t post_id);
  void send_delete_post(const int32_t requester_id, const int32_t post_id);
  void recv_delete_post();
  void list_posts(std::vector<TPost> & _return, const int32_t requester_id, const int32_t author_id);
  void send_list_posts(const int32_t requester_id, const int32_t author_id);
  void recv_list_posts(std::vector<TPost> & _return);
  int32_t count_posts_by_author(const int32_t requester_id, const int32_t author_id);
  void send_count_posts_by_author(const int32_t requester_id, const int32_t author_id);
  int32_t recv_count_posts_by_author();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class TPostServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<TPostServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (TPostServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_create_post(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_retrieve_standard_post(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_retrieve_expanded_post(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_delete_post(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_list_posts(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_count_posts_by_author(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  TPostServiceProcessor(::std::shared_ptr<TPostServiceIf> iface) :
    iface_(iface) {
    processMap_["create_post"] = &TPostServiceProcessor::process_create_post;
    processMap_["retrieve_standard_post"] = &TPostServiceProcessor::process_retrieve_standard_post;
    processMap_["retrieve_expanded_post"] = &TPostServiceProcessor::process_retrieve_expanded_post;
    processMap_["delete_post"] = &TPostServiceProcessor::process_delete_post;
    processMap_["list_posts"] = &TPostServiceProcessor::process_list_posts;
    processMap_["count_posts_by_author"] = &TPostServiceProcessor::process_count_posts_by_author;
  }

  virtual ~TPostServiceProcessor() {}
};

class TPostServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  TPostServiceProcessorFactory(const ::std::shared_ptr< TPostServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< TPostServiceIfFactory > handlerFactory_;
};

class TPostServiceMultiface : virtual public TPostServiceIf {
 public:
  TPostServiceMultiface(std::vector<std::shared_ptr<TPostServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~TPostServiceMultiface() {}
 protected:
  std::vector<std::shared_ptr<TPostServiceIf> > ifaces_;
  TPostServiceMultiface() {}
  void add(::std::shared_ptr<TPostServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void create_post(TPost& _return, const int32_t requester_id, const std::string& text) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->create_post(_return, requester_id, text);
    }
    ifaces_[i]->create_post(_return, requester_id, text);
    return;
  }

  void retrieve_standard_post(TPost& _return, const int32_t requester_id, const int32_t post_id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->retrieve_standard_post(_return, requester_id, post_id);
    }
    ifaces_[i]->retrieve_standard_post(_return, requester_id, post_id);
    return;
  }

  void retrieve_expanded_post(TPost& _return, const int32_t requester_id, const int32_t post_id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->retrieve_expanded_post(_return, requester_id, post_id);
    }
    ifaces_[i]->retrieve_expanded_post(_return, requester_id, post_id);
    return;
  }

  void delete_post(const int32_t requester_id, const int32_t post_id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->delete_post(requester_id, post_id);
    }
    ifaces_[i]->delete_post(requester_id, post_id);
  }

  void list_posts(std::vector<TPost> & _return, const int32_t requester_id, const int32_t author_id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->list_posts(_return, requester_id, author_id);
    }
    ifaces_[i]->list_posts(_return, requester_id, author_id);
    return;
  }

  int32_t count_posts_by_author(const int32_t requester_id, const int32_t author_id) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->count_posts_by_author(requester_id, author_id);
    }
    return ifaces_[i]->count_posts_by_author(requester_id, author_id);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class TPostServiceConcurrentClient : virtual public TPostServiceIf {
 public:
  TPostServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  TPostServiceConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void create_post(TPost& _return, const int32_t requester_id, const std::string& text);
  int32_t send_create_post(const int32_t requester_id, const std::string& text);
  void recv_create_post(TPost& _return, const int32_t seqid);
  void retrieve_standard_post(TPost& _return, const int32_t requester_id, const int32_t post_id);
  int32_t send_retrieve_standard_post(const int32_t requester_id, const int32_t post_id);
  void recv_retrieve_standard_post(TPost& _return, const int32_t seqid);
  void retrieve_expanded_post(TPost& _return, const int32_t requester_id, const int32_t post_id);
  int32_t send_retrieve_expanded_post(const int32_t requester_id, const int32_t post_id);
  void recv_retrieve_expanded_post(TPost& _return, const int32_t seqid);
  void delete_post(const int32_t requester_id, const int32_t post_id);
  int32_t send_delete_post(const int32_t requester_id, const int32_t post_id);
  void recv_delete_post(const int32_t seqid);
  void list_posts(std::vector<TPost> & _return, const int32_t requester_id, const int32_t author_id);
  int32_t send_list_posts(const int32_t requester_id, const int32_t author_id);
  void recv_list_posts(std::vector<TPost> & _return, const int32_t seqid);
  int32_t count_posts_by_author(const int32_t requester_id, const int32_t author_id);
  int32_t send_count_posts_by_author(const int32_t requester_id, const int32_t author_id);
  int32_t recv_count_posts_by_author(const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif
