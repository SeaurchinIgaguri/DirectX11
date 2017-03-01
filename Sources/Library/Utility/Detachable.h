#pragma once

namespace utility
{

	class Detachable
	{

	public:
		
		void Detach()
		{
			//ASSERT(isDetached != true)?	

			if (isDetached_ != true)
			{
				delete this;
				isDetached_ = true;
			}
		}

		bool IsDetached() const
		{
			return isDetached_;
		}

	private:
		bool isDetached_ = false;


	};	// end of class Detachable

}	// end of namespace utility
