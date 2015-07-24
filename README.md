drupalcamp_migrate
=================

After colony 191, after having defeated most of everyone, the pilots have now retired and have gone on speaking tours.

## DrupalCamp Data Migration

Please use `drush` to run the migration. Some common migrations are:

```
drush ms = migration status
drush mi <migration group name> = migrate import
drush mr <migration group name> = migrate rollback
drush mr --all = rollback all migrations
```

### Other drush commands:

Use the following if a migration error of 'killed' is returned
```
drush migrate-stop
drush migrate-reset-status (mrs)
```

Also make sure to run `drush cc` all before running a big migration to free up memory.
Recommend to have at least 1 gig of memory allocated when running migrations.
