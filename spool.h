
		#ifndef LVV_SPOOL
		#define LVV_SPOOL

	#include <cassert>
	#include <cstdint>
	#include <cstring>
	#include <limits>

		namespace lvv {

			template <size_t STRING_MAX, size_t POOL_SIZE,  typename OFFSET_t>
struct  buffer_t {
		OFFSET_t		last;			// offset to last string
		OFFSET_t		buf_end;		// offset to +1 past buffer end
		char			pool [POOL_SIZE];

	explicit	buffer_t() :  last(0)  { pool[0] = '\0';};
 };


			template <
				typename	BUF_INDEX_t,
				typename	OFFSET_t
			>
struct  spool_ref_t  {
		uint8_t		buf;
		uint32_t	offset;
	spool_ref_t (BUF_INDEX_t buf, OFFSET_t offset) :  buf(buf),  offset(offset)  {};
	spool_ref_t ()                                 :  buf(0)  ,  offset(0)       {};
};

			template  <
				size_t		STRING_MAX	= 256,
				size_t		POOL_SIZE	= 100000000,	// 100MB
				typename	BUF_INDEX_t	= uint8_t,
				typename	OFFSET_t	= uint32_t,
				BUF_INDEX_t	BUF_LIST_MAX	= 100
			>
struct  spool_t {
			typedef  buffer_t<STRING_MAX, POOL_SIZE, uint32_t>	buf_t;
			typedef  spool_ref_t<BUF_INDEX_t, OFFSET_t>		ref_t;
			//typedef  spool_t<STRING_MAX, POOL_SIZE, BUF_INDEX_t, OFFSET_t, BUF_LIST_MAX>		type;
		buf_t *		buf_list [BUF_LIST_MAX];
		BUF_INDEX_t	buf_list_last;

		static const size_t	string_max = STRING_MAX;

	explicit	spool_t () {  buf_list[0] = new buf_t;   buf_list_last=0; }

	char*		get (const ref_t  ref)  {
							assert (ref.buf <= buf_list_last);
		buf_t* bp = buf_list[ref.buf];		assert (ref.offset <= bp->last);
		return  bp->pool+ref.offset;
	};

	char*		get_new (ref_t& ref) {
									assert ( BUF_LIST_MAX < std::numeric_limits<BUF_INDEX_t>::max());
		buf_t* bp = buf_list [buf_list_last];
		size_t  len = strlen(bp->pool+bp->last);
		OFFSET_t  end = bp->last + len + 1;

		// new buf?
		if (end + STRING_MAX+1  >  POOL_SIZE)  {
			buf_list_last += 1;
					assert(buf_list_last < BUF_LIST_MAX);
			bp = buf_list[buf_list_last] = new buf_t();
			end = 0;
		} else {
			bp->last = end;
		}

		ref.buf = buf_list_last;
		ref.offset = end;

		bp->pool[end] = '\0';			// in case string writing will fail
		return  bp->pool + end;
	} ;
 };
			};	// namespace lvv
			#endif
