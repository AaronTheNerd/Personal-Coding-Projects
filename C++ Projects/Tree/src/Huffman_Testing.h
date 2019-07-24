// Written by Aaron Barge
// Copyright 2019
#ifndef _TREE_HUFFMAN_TESTING_CC_
#define _TREE_HUFFMAN_TESTING_CC_
#include <iostream>
#include <string>
#include "../Forest/Tree.h"
#include "../Forest/Huffman.h"
#endif 

struct HUFFMAN_TESTER {
  static bool testHuffmanTree(Huffman* t) {
    std::cout << "Testing Huffman Tree" << std::endl;
    bool result = true;
    std::cout << "Adding values..." << std::endl;
    t->Add(std::string("some stuff to add like apples bananas and other fruit"));
    std::cout << "Values added successfully" << std::endl;
    t->PrintTop();
    std::cout << "The size of the tree is currently: " << t->Size() << std::endl;
    std::cout << "The maximum depth of the tree is currentlty: " << t->MaxDepth() << std::endl;
    t->Print();
    std::cout << "Adding additional values" << std::endl;
    t->Add(std::string(" heres some more stuff to make sure more text can be added"));
    t->Add(std::string(" A Midsummer Night’s Dream opens with Theseus and Hippolyta planning their wedding, which takes place in four days. Egeus enters with his daughter, Hermia, and her two suitors, Lysander and Demetrius. Hermia is in love with Lysander, but her father wants her to marry Demetrius. He declares that if Hermia won’t marry Demetrius, she will die. Lysander and Hermia decide to escape to Athens. Helena is in love with Demeterius. Hermia and Lysander then tell Helena about their plan to leave. In a last effort to gain Demetrius’ love, Helena decides to tell him of this plot. Peter Quince is directing a group of amateur actors to perform “Pyramus and Thisbe” for Theseus’ wedding. Nick Bottom, a terrible actor, is given the lead role. Fairy Queen Titania and Fairy King Oberon are arguing because Titania refuses to give Oberon custody of the Indian boy she is raising. Oberon sends Puck, his trouble-making jester, out to find a plant called love-in-idleness, the juice of which makes any person dote on the next creature he or she sees. Taking pity on Helena for the terrible way Demetrius is treating her, Oberon instructs Puck to put some love juice in Demetrius’ eyes at a moment when Helena will be the first person he sees upon waking. Mistaking Lysander for the Demetrius Puck puts love juice in Lysander’s eyes. Still in pursuit of Demetrius, Helena wanders past and awakens the sleeping Lysander; he immediately falls in love with her. When Titania falls asleep, Oberon squeezes the love juice in her eyes. Puck, appalled by the awful acting of Bottom, gives him a donkey-head.  Bottom is unaware of the transformation and walks through the woods, waking Titania who immediately falls in love with him. Titania willingly releases the Indian boy to Oberon because she only has eyes for Bottom. Oberon’s plan is now complete so he releases her from the spell and has Puck remove the donkey-head from Bottom. Both Lysander and Demetrius are in love with Helena.  Before a serious fight breaks out between Demetrius and Lysander, Oberon has Puck create a fog that will keep the lovers from finding one another. While they are sleeping, Puck reverses the spell on Lysander. He also casts a spell so none of the lovers will remember what has happened in the woods. “Lord, what fools these mortals be!” In the final scene, the joyous lovers enter, and Theseus decides it is time to plan the festivities for the evening and chooses to see “Pyramus and Thisbe” performed. The players finally present their hilarious play."));
    std::cout << "Values added successfully" << std::endl;
    std::cout << "The size of the tree is currently: " << t->Size() << std::endl;
    std::cout << "The maximum depth of the tree is currentlty: " << t->MaxDepth() << std::endl;
    t->Print();
    std::string encoded_text = t->Encode();
    std::cout << "Encoded text:" << encoded_text << std::endl;
    std::cout << "Decoded text:" << t->Decode(encoded_text) << std::endl;
    std::cout << "Entire character set: '" << t->Top() <<"'" << std::endl;
    std::cout << "Testing contains a contained character " << (t->Contains("f") ? "PASSED" : "FAILED") << std::endl;
    std::cout << "Huffman Tree testing has " << (result ? "PASSED" : "FAILED") << std::endl;
    return result;
  }
};