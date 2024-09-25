BEGIN;
--
-- Create model User
--
CREATE TABLE "user" ("password" varchar(128) NOT NULL, "last_login" datetime NULL, "is_superuser" bool NOT NULL, "username" varchar(150) NOT NULL UNIQUE, "is_staff" bool NOT NULL, "is_active" bool NOT NULL, "date_joined" datetime NOT NULL, "id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "email" varchar(256) NOT NULL UNIQUE, "first_name" varchar(128) NOT NULL, "last_name" varchar(128) NOT NULL, "profile_photo" varchar(100) NULL);
CREATE TABLE "user_groups" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED, "group_id" integer NOT NULL REFERENCES "auth_group" ("id") DEFERRABLE INITIALLY DEFERRED);
CREATE TABLE "user_user_permissions" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED, "permission_id" integer NOT NULL REFERENCES "auth_permission" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Create model Category
--
CREATE TABLE "category" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "image" varchar(100) NULL, "name" varchar(255) NOT NULL);
--
-- Create model Order
--
CREATE TABLE "order" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "display_name" varchar(255) NOT NULL, "cost" real NOT NULL, "status" integer NOT NULL);
--
-- Create model Product
--
CREATE TABLE "product" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "archived" bool NOT NULL, "description" text NOT NULL, "name" varchar(255) NOT NULL, "code" varchar(255) NULL, "price" integer NOT NULL, "quantity" integer NOT NULL, "size" varchar(50) NOT NULL, "category_id" bigint NOT NULL REFERENCES "category" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Create model Shop
--
CREATE TABLE "shop" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "image" varchar(100) NULL, "link" varchar(50) NOT NULL, "name" varchar(255) NOT NULL);
--
-- Create model UserLocation
--
CREATE TABLE "userlocation" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "address" varchar(255) NOT NULL, "latitude" real NOT NULL, "longitude" real NOT NULL, "name" varchar(255) NOT NULL, "mobile_phone" varchar(20) NOT NULL, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Create model SubCategory
--
CREATE TABLE "subcategory" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "name" varchar(255) NOT NULL, "category_id" bigint NOT NULL REFERENCES "category" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Create model ShopManager
--
CREATE TABLE "shopmanager" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "shop_id" bigint NOT NULL REFERENCES "shop" ("id") DEFERRABLE INITIALLY DEFERRED, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Add field location to shop
--
ALTER TABLE "shop" ADD COLUMN "location_id" bigint NULL REFERENCES "userlocation" ("id") DEFERRABLE INITIALLY DEFERRED;
--
-- Add field owner to shop
--
CREATE TABLE "new__shop" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "image" varchar(100) NULL, "link" varchar(50) NOT NULL, "name" varchar(255) NOT NULL, "location_id" bigint NULL REFERENCES "userlocation" ("id") DEFERRABLE INITIALLY DEFERRED, "owner_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "new__shop" ("id", "created_at", "updated_at", "image", "link", "name", "location_id", "owner_id") SELECT "id", "created_at", "updated_at", "image", "link", "name", "location_id", NULL FROM "shop";
DROP TABLE "shop";
ALTER TABLE "new__shop" RENAME TO "shop";
CREATE UNIQUE INDEX "user_groups_user_id_group_id_uniq" ON "user_groups" ("user_id", "group_id");
CREATE INDEX "user_groups_user_id" ON "user_groups" ("user_id");
CREATE INDEX "user_groups_group_id" ON "user_groups" ("group_id");
CREATE UNIQUE INDEX "user_user_permissions_user_id_permission_id_uniq" ON "user_user_permissions" ("user_id", "permission_id");
CREATE INDEX "user_user_permissions_user_id" ON "user_user_permissions" ("user_id");
CREATE INDEX "user_user_permissions_permission_id" ON "user_user_permissions" ("permission_id");
CREATE INDEX "product_category_id" ON "product" ("category_id");
CREATE INDEX "userlocation_user_id" ON "userlocation" ("user_id");
CREATE INDEX "subcategory_category_id" ON "subcategory" ("category_id");
CREATE INDEX "shopmanager_shop_id" ON "shopmanager" ("shop_id");
CREATE INDEX "shopmanager_user_id" ON "shopmanager" ("user_id");
CREATE INDEX "shop_location_id" ON "shop" ("location_id");
CREATE INDEX "shop_owner_id" ON "shop" ("owner_id");
--
-- Create model Sale
--
CREATE TABLE "sale" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "customer_name" varchar(255) NULL, "customer_contact" varchar(255) NULL, "price" integer NOT NULL, "quantity" integer NOT NULL, "product_id" bigint NOT NULL REFERENCES "product" ("id") DEFERRABLE INITIALLY DEFERRED, "shop_id" bigint NOT NULL REFERENCES "shop" ("id") DEFERRABLE INITIALLY DEFERRED, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Create model ProductImage
--
CREATE TABLE "productimage" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "image_file" varchar(100) NULL, "product_id" bigint NOT NULL REFERENCES "product" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Add field shop to product
--
CREATE TABLE "new__product" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "archived" bool NOT NULL, "description" text NOT NULL, "name" varchar(255) NOT NULL, "code" varchar(255) NULL, "price" integer NOT NULL, "quantity" integer NOT NULL, "size" varchar(50) NOT NULL, "category_id" bigint NOT NULL REFERENCES "category" ("id") DEFERRABLE INITIALLY DEFERRED, "shop_id" bigint NOT NULL REFERENCES "shop" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "new__product" ("id", "created_at", "updated_at", "archived", "description", "name", "code", "price", "quantity", "size", "category_id", "shop_id") SELECT "id", "created_at", "updated_at", "archived", "description", "name", "code", "price", "quantity", "size", "category_id", NULL FROM "product";
DROP TABLE "product";
ALTER TABLE "new__product" RENAME TO "product";
CREATE INDEX "sale_product_id" ON "sale" ("product_id");
CREATE INDEX "sale_shop_id" ON "sale" ("shop_id");
CREATE INDEX "sale_user_id" ON "sale" ("user_id");
CREATE INDEX "productimage_product_id" ON "productimage" ("product_id");
CREATE INDEX "product_category_id" ON "product" ("category_id");
CREATE INDEX "product_shop_id" ON "product" ("shop_id");
--
-- Add field subcategory to product
--
ALTER TABLE "product" ADD COLUMN "subcategory_id" bigint NULL REFERENCES "subcategory" ("id") DEFERRABLE INITIALLY DEFERRED;
--
-- Create model OrderItem
--
CREATE TABLE "orderitem" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "order_id" bigint NOT NULL REFERENCES "order" ("id") DEFERRABLE INITIALLY DEFERRED, "product_id" bigint NOT NULL REFERENCES "product" ("id") DEFERRABLE INITIALLY DEFERRED);
--
-- Add field delivery_location to order
--
CREATE TABLE "new__order" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "display_name" varchar(255) NOT NULL, "cost" real NOT NULL, "status" integer NOT NULL, "delivery_location_id" bigint NOT NULL REFERENCES "userlocation" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "new__order" ("id", "created_at", "updated_at", "display_name", "cost", "status", "delivery_location_id") SELECT "id", "created_at", "updated_at", "display_name", "cost", "status", NULL FROM "order";
DROP TABLE "order";
ALTER TABLE "new__order" RENAME TO "order";
CREATE INDEX "product_subcategory_id" ON "product" ("subcategory_id");
CREATE INDEX "orderitem_order_id" ON "orderitem" ("order_id");
CREATE INDEX "orderitem_product_id" ON "orderitem" ("product_id");
CREATE INDEX "order_delivery_location_id" ON "order" ("delivery_location_id");
--
-- Add field user to order
--
CREATE TABLE "new__order" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "display_name" varchar(255) NOT NULL, "cost" real NOT NULL, "status" integer NOT NULL, "delivery_location_id" bigint NOT NULL REFERENCES "userlocation" ("id") DEFERRABLE INITIALLY DEFERRED, "user_id" bigint NOT NULL REFERENCES "user" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "new__order" ("id", "created_at", "updated_at", "display_name", "cost", "status", "delivery_location_id", "user_id") SELECT "id", "created_at", "updated_at", "display_name", "cost", "status", "delivery_location_id", NULL FROM "order";
DROP TABLE "order";
ALTER TABLE "new__order" RENAME TO "order";
CREATE INDEX "order_delivery_location_id" ON "order" ("delivery_location_id");
CREATE INDEX "order_user_id" ON "order" ("user_id");
--
-- Add field shop to category
--
CREATE TABLE "new__category" ("id" bigint unsigned NOT NULL PRIMARY KEY CHECK ("id" >= 0), "created_at" datetime NOT NULL, "updated_at" datetime NOT NULL, "image" varchar(100) NULL, "name" varchar(255) NOT NULL, "shop_id" bigint NOT NULL REFERENCES "shop" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "new__category" ("id", "created_at", "updated_at", "image", "name", "shop_id") SELECT "id", "created_at", "updated_at", "image", "name", NULL FROM "category";
DROP TABLE "category";
ALTER TABLE "new__category" RENAME TO "category";
CREATE INDEX "category_shop_id" ON "category" ("shop_id");
COMMIT;
