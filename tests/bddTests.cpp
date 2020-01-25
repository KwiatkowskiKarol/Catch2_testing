#include <catch2/catch.hpp>
#include <database.hpp>
#include <map>
#include <memory>
#include <list>

using namespace std;
struct bddTests{
  int id;
  string rentCar;
};

ostream & operator<<(ostream &o, const bddTests &d) {
    o<<"[" << d.id << ", " << d.rentCar << "]";
    return o;
}

TEST_CASE("Object operations on database", "[database_c][constructors]") {

  SECTION("Object can be created") {

    REQUIRE_NOTHROW([]() { database_c<bddTests> db; });
  }
  SECTION("Simple injection apply to works") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    REQUIRE_FALSE(db.get_container() == nullptr);
    REQUIRE(db.get_container() == container.get());
  }
}

TEST_CASE("Getting data from the database", "[database_c][get_all]") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    SECTION("get all records") {
        REQUIRE_NOTHROW( db.get_all() );
    }
    SECTION("get all records") {
        list<bddTests> ret_list = db.get_all();
        REQUIRE(ret_list.size() == 0);
    }
    SECTION("get all records") {
        (*container)[0] = {0,"Opel"};
        list<bddTests> ret_list = db.get_all();
        REQUIRE(db.get_container() == container.get());
        REQUIRE(db.get_container()->size() ==1);
        REQUIRE(ret_list.size() == 1);
    }
}

SCENARIO("getting data from database","[database_c][bdd][get_all]") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    GIVEN("Database contain records") {
        (*container)[0] = {0,"Opel"};
        (*container)[1] = {1,"VW"};
        (*container)[2] = {2,"Audi"};
        (*container)[3] = {3,"Skoda"};

        INFO((*container)[0]);
        WHEN("get data from the database") {
            list<bddTests> ret_list = db.get_all();

            THEN("the list should contain 4 elements") {
                CHECK(ret_list.size() == 4);
            }

            THEN("the list should contain element with car Opel") {
                bddTests found;
                for (auto e:ret_list) {
                    if (e.rentCar == "Opel") found = e;
                }
                REQUIRE(found.rentCar =="Opel");
            }
        }
    }
}


SCENARIO("Add data to database","[database_c][bdd][create]") {
    auto container = make_shared<map<int, bddTests>>();
    auto e;
    database_c<bddTests> db(container);
    GIVEN("create entity") {
        e = {0,"Seat"};

        INFO((*container)[0]);
        WHEN("call add method") {
            list<bddTests> ret_list = db.create(e);

            THEN("the list should contain 1 element") {
                CHECK(ret_list.size() == 1);
            }

            THEN("the list should contain element with the car Seat") {
                bddTests found;
                for (auto e:ret_list) {
                    if (e.rentCar == "Seat") found = e;
                }
                REQUIRE(found.rentCar =="Seat");
            }
        }
    }
}


SCENARIO("Get data by ID from database","[database_c][bdd][getById]") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    GIVEN("create some test data") {
        (*container)[0] = {0,"Ford"};
        (*container)[1] = {1,"Fiat"};
        (*container)[2] = {2,"Renault"};

        INFO((*container)[0]);
        WHEN("call method add") {
            bddTests ret = db.getById(0);

            THEN("should get element different from null") {
                CHECK(ret != NULL);
            }

            THEN("should been car Ford") {
                CHECK(ret.rentCar == "Ford");
            }
        }
    }
}

SCENARIO("Get data by ID from database","[database_c][bdd][update]") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    GIVEN("create some test data") {
        (*container)[0] = {0,"Ford"};
        (*container)[1] = {1,"Fiat"};
        (*container)[2] = {2,"Renault"};

        INFO((*container)[0]);
        WHEN("call add method") {
            bddTests ret = db.update("Reserved", 0);

            THEN("Still should be same value in element of list") {
                CHECK(ret_list.size() == 3);
            }

            THEN("should get element witch changed car") {
                CHECK(ret == "Reserved");
            }
        }
    }
}


SCENARIO("Remove data from database","[database_c][bdd][deleteById]") {
    auto container = make_shared<map<int, bddTests>>();
    database_c<bddTests> db(container);
    GIVEN("create some test data") {
        (*container)[0] = {0,"Ford"};
        (*container)[1] = {1,"Fiat"};
        (*container)[2] = {2,"Renault"};


        INFO((*container)[0]);
        WHEN("call add method") {
            list<bddTests> ret_list = db.deleteById(0);

            THEN("the list should contain 2 elements") {
                CHECK(ret_list.size() == 2);
            }

            THEN("the list should not contain element with the car Fiat") {
                bddTests found;
                for (auto e:ret_list) {
                    if (e.rentCar == "Fiat") found = e;
                }
                CHECK(found == NULL);
            }
        }
    }
}
