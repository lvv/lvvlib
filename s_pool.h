
	#include <cassert>
	#include <cstdint>
	#include <cstring>


		template <size_t STRING_MAX, size_t POOL_SIZE,  typename OFFSET_t>
struct  buffer_t {
		OFFSET_t		last;			// offset to last string
		OFFSET_t		buf_end;		// offset to +1 past buffer end
		char			pool [POOL_SIZE];

	explicit	buffer_t() :  last(0)  { pool[0] = '\0';};
 };


struct  spool_ref_t  { uint8_t	buf;	uint32_t  offset; };


		template  <
			size_t		STRING_MAX	= 256,
			size_t		POOL_SIZE	= 100000000,	// 100MB
			typename	OFFSET_t	= uint32_t,	// always > 0
			typename	BUF_INDEX_t	= uint8_t,
			BUF_INDEX_t	BUF_LIST_MAX	= 1000
		>

struct  spool_t {

			typedef  buffer_t<STRING_MAX, POOL_SIZE, uint32_t>	  buf_t;

		buf_t *		buf_list [BUF_LIST_MAX];
		OFFSET_t		buf_list_last;

	explicit	spool_t () {  buf_list[0] = new buf_t;   buf_list_last=0; }


	char*		get (const spool_ref_t  ref)  {
							assert (ref.buf <= buf_list_last);
		buf_t* bp = buf_list[ref.buf];		assert (ref.offset <= bp->last);
		return  bp->pool+ref.offset;
	};


	char*		get_new (spool_ref_t& ref) {
		buf_t* bp = buf_list [buf_list_last];
		size_t  len = strlen(bp->pool+bp->last);
		OFFSET_t  end = bp->last + len + 1;
		
		// new buf?
		if (end + STRING_MAX+1  >  POOL_SIZE)  {	
					assert(buf_list_last < BUF_LIST_MAX);
			buf_list_last += 1;	
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
