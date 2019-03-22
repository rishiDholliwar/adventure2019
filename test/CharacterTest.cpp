#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <Character.h>


const ID DEFAULT_ROOM = 1000;

TEST(CharacterTest, CharacterTest_Character_Empty_Constructor_Test) {
    Character testCharacter;
    ID expectedUniqueID = 1;

    ASSERT_EQ(expectedUniqueID, testCharacter.getID());
    ASSERT_TRUE(testCharacter.getName().empty());

}


TEST(CharacterTest, CharacterTest_Character_Add_To_Inventory_Test) {

    std::string objectName = "Basic Sword";
    Character testCharacter("TestCharacter", DEFAULT_ROOM);

    Object testObject(objectName);
    testCharacter.addItemToInventory(testObject);

    ASSERT_TRUE(testCharacter.hasItem(objectName));
}

TEST(CharacterTest, CharacterTest_Character_Delete_Item_Test) {

    std::string objectName = "Basic Sword";
    Character testCharacter("TestCharacter", DEFAULT_ROOM);

    Object testObject(objectName);
    testCharacter.addItemToInventory(testObject);

    testCharacter.dropItem(objectName);

    ASSERT_FALSE(testCharacter.hasItem(objectName));
}

TEST(CharacterTest, CharacterTest_Character_Wearing_Item_Test) {
    std::string objectName = "Basic Sword";
    Character testCharacter("TestCharacter", DEFAULT_ROOM);

    Object testObject(objectName);
    testCharacter.addItemToInventory(testObject);

    testCharacter.wear(objectName);

    ASSERT_TRUE(testCharacter.isWearing(objectName));
    ASSERT_FALSE(testCharacter.hasItem(objectName));
}

TEST(CharacterTest, CharacterTest_Character_TakeOff_Item_Test) {
    std::string objectName = "Basic Sword";
    Character testCharacter("TestCharacter", DEFAULT_ROOM);

    Object testObject(objectName);
    testCharacter.addItemToInventory(testObject);

    testCharacter.wear(objectName);

    testCharacter.remove(objectName);

    ASSERT_FALSE(testCharacter.isWearing(objectName));
    ASSERT_TRUE(testCharacter.hasItem(objectName));
}

