//
//  NonMovable.cpp
//  Assignment_2_Jinwoo_Lee
//
//  Created by JINWOO LEE on 28/04/20.
//

#ifndef NonCopyable_hpp
#define NonCopyable_hpp

class NonMovable {
  public:
    NonMovable(NonMovable &&) = delete;

    NonMovable &operator=(NonMovable &&) = delete;

  protected:
    NonMovable() = default;
};


#endif /* NonMovable_hpp */

