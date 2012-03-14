#ifndef BOOST_NETWORK_PROTOCOL_HTTP_REQUEST_BASE_HPP_20111008
#define BOOST_NETWORK_PROTOCOL_HTTP_REQUEST_BASE_HPP_20111008

// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NETWORK_BUFFER_CHUNK
#define BOOST_NETWORK_BUFFER_CHUNK 1024  // We want 1KiB worth of data at least.
#endif

#include <boost/network/message/message_base.hpp>
#include <boost/network/uri/uri.hpp>

namespace boost { namespace network { namespace http {

struct body_source : iostreams::source {
  virtual std::streamsize read(char * buffer, std::streamsize size);
  virtual ~body_source();
};

struct request_storage_base_pimpl;

struct request_storage_base {
 protected:
  request_storage_base(size_t chunk_size = BOOST_NETWORK_BUFFER_CHUNK);
  request_storage_base(request_storage_base const &other);
  virtual void append(char const *data, size_t size);
  virtual size_t read(char *destination, size_t offset, size_t size) const;
  virtual void flatten(std::string &destination) const;
  virtual void clear();
  virtual bool equals(request_storage_base const &other) const;
  virtual void swap(request_storage_base &other);
  virtual ~request_storage_base();

 private:
  request_storage_base_pimpl *pimpl_;
};

struct request_base : message_base, request_storage_base {
  // Setters
  virtual void set_method(std::string const & method) = 0;
  virtual void set_status(std::string const & status) = 0;
  virtual void set_status_message(std::string const & status_message) = 0;
  virtual void set_body_writer(function<void(char*, size_t)> writer) = 0;
  virtual void set_uri(std::string const &uri) = 0;
  virtual void set_uri(network::uri::uri const &uri) = 0;

  // Getters
  virtual void get_uri(network::uri::uri &uri) const = 0;
  virtual void get_uri(std::string &uri) const = 0;
  virtual void get_method(std::string & method) const = 0;
  virtual void get_status(std::string & status) const = 0;
  virtual void get_status_message(std::string & status_message) const = 0;
  virtual void get_body(function<void(char*, size_t)> chunk_reader) const = 0;
  virtual void get_body(std::string const & body) const = 0;
  virtual ~request_base() = 0;
};

} /* http */
  
} /* network */
  
} /* boost */

#endif /* BOOST_NETWORK_PROTOCOL_HTTP_REQUEST_BASE_HPP_20111008 */
