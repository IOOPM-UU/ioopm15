struct person;

/** buildPerson
 *
 *  @arg first The first name of the person
 *  @arg last  The last name of the person
 *
 *  @returns A person named "first last", or NULL if a person
 *  could not be created
 */
struct person *buildPerson(char *first, char *last);

char *getFirstName(struct person *p);

char *getLastName(struct person *p);