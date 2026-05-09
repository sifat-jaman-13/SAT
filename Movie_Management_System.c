/* Movie Library Management System - Improved & Fixed
   Secure file handling with proper error checking
   Cross-platform compatible
   
   Improvements:
   - All functions use fgets() for safe input (already in original)
   - Fixed function signatures and return types
   - Better error handling
   - Memory leak fixes
   - Improved user interface
   - Better documentation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR_SCREEN system("cls")
#else
    #define CLEAR_SCREEN system("clear")
#endif

typedef struct
{
    char title[100];
    char genre[50];
    int year;
    char director[100];
    char language[50];
    int rating;
    char checkout_date[11];
    int is_rented;
} Movie;

void login(void);
void welcomeMenu(FILE *fptr);
void addMovie(FILE *fptr);
void searchMovieByName(FILE *fptr);
void searchMovieByDirector(FILE *fptr);
void searchMovieByLanguage(FILE *fptr);
void searchMovieByReleaseDate(FILE *fptr);
void deleteMovieByName(FILE *fptr);
void deleteMoviesByGenre(FILE *fptr);
void deleteMoviesByYear(FILE *fptr);
void deleteMoviesByDirector(FILE *fptr);
void deleteMoviesByLanguage(FILE *fptr);
void displayAllMoviesSortedByYear(FILE *fptr);
void countMovies(FILE *fptr);
void deleteLibrary(FILE *fptr);
void editMovieDetails(FILE *fptr);
void safe_fgets(char *buffer, int size);
void rateMovie(FILE *fptr);
void rentMovie(FILE *fptr);
void returnMovie(FILE *fptr);
void showGenreStatistics(FILE *fptr);
void exportToCSV(FILE *fptr);
void backupDatabase(void);
void restoreDatabase(void);

int main()
{
    FILE *fptr;

    login();

    fptr = fopen("movies.txt", "a+");
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    welcomeMenu(fptr);

    fclose(fptr);

    return 0;
}

void safe_fgets(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
    }
}

void login(void)
{
    char username[20];
    char password[20];
    int attempts = 0;

    while (attempts < 5)
    {
        CLEAR_SCREEN;

        printf("\n\n");
        printf("╔══════════════════════════════════════════╗\n");
        printf("║  MOVIE LIBRARY MANAGEMENT SYSTEM         ║\n");
        printf("║  Secure Login Required                   ║\n");
        printf("╚══════════════════════════════════════════╝\n\n");

        printf("Username: ");
        safe_fgets(username, sizeof(username));

        printf("Password: ");
        safe_fgets(password, sizeof(password));

        if (strcmp(username, "admin") == 0 && strcmp(password, "sifat") == 0)
        {
            CLEAR_SCREEN;
            printf("\n\n✓ Login Successful!\n");
            printf("Welcome to Movie Library Management System\n\n");
            printf("Press Enter to continue...");
            getchar();
            break;
        }
        else
        {
            attempts++;
            printf("\n✗ Invalid username or password.\n");
            printf("Attempts Remaining: %d\n", 5 - attempts);

            if (attempts == 5)
            {
                printf("\n✗ Maximum login attempts reached. Exiting...\n");
                exit(0);
            }

            printf("Press Enter to try again...\n");
            getchar();
        }
    }
}

void welcomeMenu(FILE *fptr)
{
    int choice;

    while (1)
    {
        CLEAR_SCREEN;
        printf("\n╔══════════════════════════════════════════╗\n");
        printf("║  MOVIE LIBRARY MAIN MENU                 ║\n");
        printf("╚══════════════════════════════════════════╝\n\n");

        printf("1. Add a Movie\n");
        printf("2. Search for a Movie\n");
        printf("3. Delete a Movie by Title\n");
        printf("4. Delete Multiple Movies\n");
        printf("5. Display All Movies (Sorted by Year)\n");
        printf("6. Edit Movie Details\n");
        printf("7. Count Movies in Library\n");
        printf("8. Rate a Movie (1-5 stars)\n");
        printf("9. Rent a Movie\n");
        printf("10. Return a Movie\n");
        printf("11. Genre Statistics\n");
        printf("12. Export to CSV\n");
        printf("13. Backup Database\n");
        printf("14. Delete Entire Library\n");
        printf("15. Exit\n\n");

        printf("Enter your choice (1-15): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            getchar();
            getchar();
            continue;
        }
        getchar();

        switch (choice)
        {
        case 1:
            addMovie(fptr);
            break;
        case 2:
            CLEAR_SCREEN;
            printf("\n╔════════════════════════════════════════╗\n");
            printf("║  SEARCH OPTIONS                         ║\n");
            printf("╚════════════════════════════════════════╝\n\n");
            printf("1. Search by Title\n");
            printf("2. Search by Director\n");
            printf("3. Search by Language\n");
            printf("4. Search by Release Year\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                searchMovieByName(fptr);
                break;
            case 2:
                searchMovieByDirector(fptr);
                break;
            case 3:
                searchMovieByLanguage(fptr);
                break;
            case 4:
                searchMovieByReleaseDate(fptr);
                break;
            default:
                printf("Invalid choice.\n");
            }
            break;
        case 3:
            deleteMovieByName(fptr);
            break;
        case 4:
            CLEAR_SCREEN;
            printf("\n╔════════════════════════════════════════╗\n");
            printf("║  DELETE MULTIPLE MOVIES                 ║\n");
            printf("╚════════════════════════════════════════╝\n\n");
            printf("1. Delete by Genre\n");
            printf("2. Delete by Year\n");
            printf("3. Delete by Director\n");
            printf("4. Delete by Language\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
            case 1:
                deleteMoviesByGenre(fptr);
                break;
            case 2:
                deleteMoviesByYear(fptr);
                break;
            case 3:
                deleteMoviesByDirector(fptr);
                break;
            case 4:
                deleteMoviesByLanguage(fptr);
                break;
            default:
                printf("Invalid choice.\n");
            }
            break;
        case 5:
            displayAllMoviesSortedByYear(fptr);
            break;
        case 6:
            editMovieDetails(fptr);
            break;
        case 7:
            countMovies(fptr);
            break;
        case 8:
            rateMovie(fptr);
            break;
        case 9:
            rentMovie(fptr);
            break;
        case 10:
            returnMovie(fptr);
            break;
        case 11:
            showGenreStatistics(fptr);
            break;
        case 12:
            exportToCSV(fptr);
            break;
        case 13:
            backupDatabase();
            break;
        case 14:
            deleteLibrary(fptr);
            break;
        case 15:
            printf("Exiting... Thank you for using Movie Library!\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }
}

void addMovie(FILE *fptr)
{
    Movie movie;
    memset(&movie, 0, sizeof(Movie));

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  ADD A NEW MOVIE                       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Title: ");
    safe_fgets(movie.title, sizeof(movie.title));

    printf("Genre: ");
    safe_fgets(movie.genre, sizeof(movie.genre));

    printf("Year: ");
    if (scanf("%d", &movie.year) != 1)
    {
        printf("Invalid year input.\n");
        getchar();
        return;
    }
    getchar();

    printf("Director: ");
    safe_fgets(movie.director, sizeof(movie.director));

    printf("Language: ");
    safe_fgets(movie.language, sizeof(movie.language));

    movie.rating = 0;
    movie.is_rented = 0;
    strcpy(movie.checkout_date, "");

    if (fwrite(&movie, sizeof(Movie), 1, fptr) != 1)
    {
        printf("Error writing movie to file.\n");
    }
    else
    {
        printf("\n✓ Movie added successfully!\n");
    }
}

void searchMovieByName(FILE *fptr)
{
    char searchTitle[100];
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  SEARCH BY TITLE                       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the title to search: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strstr(movie.title, searchTitle) != NULL)
        {
            printf("\n┌────────────────────────────────────────┐\n");
            printf("│ MOVIE FOUND\n");
            printf("├────────────────────────────────────────┤\n");
            printf("│ Title: %s\n", movie.title);
            printf("│ Genre: %s\n", movie.genre);
            printf("│ Year: %d\n", movie.year);
            printf("│ Director: %s\n", movie.director);
            printf("│ Language: %s\n", movie.language);
            printf("└────────────────────────────────────────┘\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Movie not found.\n");
    }
}

void searchMovieByDirector(FILE *fptr)
{
    char searchDirector[100];
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  SEARCH BY DIRECTOR                    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the director to search: ");
    safe_fgets(searchDirector, sizeof(searchDirector));

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strstr(movie.director, searchDirector) != NULL)
        {
            printf("\n┌────────────────────────────────────────┐\n");
            printf("│ MOVIE FOUND\n");
            printf("├────────────────────────────────────────┤\n");
            printf("│ Title: %s\n", movie.title);
            printf("│ Genre: %s\n", movie.genre);
            printf("│ Year: %d\n", movie.year);
            printf("│ Director: %s\n", movie.director);
            printf("│ Language: %s\n", movie.language);
            printf("└────────────────────────────────────────┘\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Movie not found.\n");
    }
}

void searchMovieByLanguage(FILE *fptr)
{
    char searchLanguage[50];
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  SEARCH BY LANGUAGE                    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the language to search: ");
    safe_fgets(searchLanguage, sizeof(searchLanguage));

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strstr(movie.language, searchLanguage) != NULL)
        {
            printf("\n┌────────────────────────────────────────┐\n");
            printf("│ MOVIE FOUND\n");
            printf("├────────────────────────────────────────┤\n");
            printf("│ Title: %s\n", movie.title);
            printf("│ Genre: %s\n", movie.genre);
            printf("│ Year: %d\n", movie.year);
            printf("│ Director: %s\n", movie.director);
            printf("│ Language: %s\n", movie.language);
            printf("└────────────────────────────────────────┘\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Movie not found.\n");
    }
}

void searchMovieByReleaseDate(FILE *fptr)
{
    int searchYear;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  SEARCH BY RELEASE YEAR                ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the year to search: ");
    if (scanf("%d", &searchYear) != 1)
    {
        printf("Invalid year input.\n");
        return;
    }
    getchar();

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (movie.year == searchYear)
        {
            printf("\n┌────────────────────────────────────────┐\n");
            printf("│ MOVIE FOUND\n");
            printf("├────────────────────────────────────────┤\n");
            printf("│ Title: %s\n", movie.title);
            printf("│ Genre: %s\n", movie.genre);
            printf("│ Year: %d\n", movie.year);
            printf("│ Director: %s\n", movie.director);
            printf("│ Language: %s\n", movie.language);
            printf("└────────────────────────────────────────┘\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("No movies found from year %d.\n", searchYear);
    }
}

void deleteMovieByName(FILE *fptr)
{
    char searchTitle[100];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE MOVIE BY TITLE                 ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the title to delete: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.title, searchTitle) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("✓ Movie deleted successfully.\n");
    }
    else
    {
        printf("✗ Movie not found.\n");
    }
}

void deleteMoviesByGenre(FILE *fptr)
{
    char searchGenre[50];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE MOVIES BY GENRE                ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the genre to delete: ");
    safe_fgets(searchGenre, sizeof(searchGenre));

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.genre, searchGenre) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("✓ Movies deleted successfully.\n");
    }
    else
    {
        printf("✗ No movies found with genre '%s'.\n", searchGenre);
    }
}

void deleteMoviesByYear(FILE *fptr)
{
    int searchYear;
    FILE *tempFile;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE MOVIES BY YEAR                 ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the year to delete: ");
    if (scanf("%d", &searchYear) != 1)
    {
        printf("Invalid year input.\n");
        return;
    }
    getchar();

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (movie.year != searchYear)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("✓ Movies from year %d deleted successfully.\n", searchYear);
    }
    else
    {
        printf("✗ No movies found from year %d.\n", searchYear);
    }
}

void deleteMoviesByDirector(FILE *fptr)
{
    char searchDirector[100];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE MOVIES BY DIRECTOR             ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the director to delete: ");
    safe_fgets(searchDirector, sizeof(searchDirector));

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.director, searchDirector) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("✓ Movies by director '%s' deleted successfully.\n", searchDirector);
    }
    else
    {
        printf("✗ No movies found by director '%s'.\n", searchDirector);
    }
}

void deleteMoviesByLanguage(FILE *fptr)
{
    char searchLanguage[50];
    FILE *tempFile;
    Movie movie;
    int found = 0;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE MOVIES BY LANGUAGE             ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("Enter the language to delete: ");
    safe_fgets(searchLanguage, sizeof(searchLanguage));

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        return;
    }

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        if (strcmp(movie.language, searchLanguage) != 0)
        {
            fwrite(&movie, sizeof(Movie), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(tempFile);

    remove("movies.txt");
    rename("temp.txt", "movies.txt");

    fptr = fopen("movies.txt", "a+");

    if (found)
    {
        printf("✓ Movies in '%s' deleted successfully.\n", searchLanguage);
    }
    else
    {
        printf("✗ No movies found in language '%s'.\n", searchLanguage);
    }
}

void displayAllMoviesSortedByYear(FILE *fptr)
{
    int count = 0;
    Movie *movies;
    Movie temp;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  ALL MOVIES (SORTED BY YEAR)           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    rewind(fptr);

    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        printf("No movies found in library.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);

    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (movies[j].year < movies[j + 1].year)
            {
                temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        printf("(%d) Title: %s\n", i + 1, movies[i].title);
        printf("    Genre: %s\n", movies[i].genre);
        printf("    Year: %d\n", movies[i].year);
        printf("    Director: %s\n", movies[i].director);
        printf("    Language: %s\n", movies[i].language);
        printf("    ═══════════════════════════════════════\n\n");
    }

    free(movies);
}

void countMovies(FILE *fptr)
{
    int count = 0;
    Movie movie;

    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  MOVIE COUNT                           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    rewind(fptr);

    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    printf("Total number of movies in library: %d\n", count);
}

void deleteLibrary(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  DELETE ENTIRE LIBRARY                 ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    printf("⚠️  WARNING: This will delete ALL movies!\n");
    printf("This action CANNOT be undone.\n\n");
    printf("Type 'YES' to confirm: ");

    char confirm[10];
    safe_fgets(confirm, sizeof(confirm));

    if (strcmp(confirm, "YES") == 0)
    {
        if (remove("movies.txt") == 0)
        {
            printf("✓ Library deleted successfully.\n");
            fptr = fopen("movies.txt", "a+");
        }
        else
        {
            printf("✗ Error deleting library.\n");
        }
    }
    else
    {
        printf("Operation cancelled.\n");
    }
}

void editMovieDetails(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  EDIT MOVIE DETAILS                    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    char searchTitle[100];
    printf("Enter movie title to edit: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    int count = 0;
    Movie *movies;
    Movie temp;

    rewind(fptr);

    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);

    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
    {
        count++;
    }

    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Movie not found.\n");
        free(movies);
        return;
    }

    printf("\nCurrent details:\n");
    printf("Title: %s\n", movies[foundIndex].title);
    printf("Genre: %s\n", movies[foundIndex].genre);
    printf("Year: %d\n", movies[foundIndex].year);
    printf("Director: %s\n", movies[foundIndex].director);
    printf("Language: %s\n\n", movies[foundIndex].language);

    printf("Enter new details:\n");
    printf("New Title: ");
    safe_fgets(movies[foundIndex].title, sizeof(movies[foundIndex].title));

    printf("New Genre: ");
    safe_fgets(movies[foundIndex].genre, sizeof(movies[foundIndex].genre));

    printf("New Year: ");
    scanf("%d", &movies[foundIndex].year);
    getchar();

    printf("New Director: ");
    safe_fgets(movies[foundIndex].director, sizeof(movies[foundIndex].director));

    printf("New Language: ");
    safe_fgets(movies[foundIndex].language, sizeof(movies[foundIndex].language));

    rewind(fptr);
    for (int i = 0; i < count; i++)
    {
        fwrite(&movies[i], sizeof(Movie), 1, fptr);
    }

    printf("\n✓ Movie details updated successfully!\n");

    free(movies);
}

void rateMovie(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  RATE A MOVIE                         ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    char searchTitle[100];
    printf("Enter movie title to rate: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    int rating;
    printf("Enter rating (1-5 stars): ");
    if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5)
    {
        printf("Invalid rating. Please enter a number between 1-5.\n");
        getchar();
        return;
    }
    getchar();

    int count = 0;
    Movie *movies;
    Movie temp;

    rewind(fptr);
    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
        count++;

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);
    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
        count++;

    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Movie not found.\n");
        free(movies);
        return;
    }

    movies[foundIndex].rating = rating;

    rewind(fptr);
    for (int i = 0; i < count; i++)
        fwrite(&movies[i], sizeof(Movie), 1, fptr);

    printf("✓ Movie rated %d/5 stars successfully!\n", rating);
    free(movies);
}

void rentMovie(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  RENT A MOVIE                         ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    char searchTitle[100];
    printf("Enter movie title to rent: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    char checkout_date[11];
    printf("Enter checkout date (YYYY-MM-DD): ");
    safe_fgets(checkout_date, sizeof(checkout_date));

    int count = 0;
    Movie *movies;
    Movie temp;

    rewind(fptr);
    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
        count++;

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);
    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
        count++;

    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Movie not found.\n");
        free(movies);
        return;
    }

    if (movies[foundIndex].is_rented)
    {
        printf("✗ Movie is already rented.\n");
        free(movies);
        return;
    }

    movies[foundIndex].is_rented = 1;
    strcpy(movies[foundIndex].checkout_date, checkout_date);

    rewind(fptr);
    for (int i = 0; i < count; i++)
        fwrite(&movies[i], sizeof(Movie), 1, fptr);

    printf("✓ Movie rented successfully! Checkout date: %s\n", checkout_date);
    free(movies);
}

void returnMovie(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  RETURN A MOVIE                       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    char searchTitle[100];
    printf("Enter movie title to return: ");
    safe_fgets(searchTitle, sizeof(searchTitle));

    int count = 0;
    Movie *movies;
    Movie temp;

    rewind(fptr);
    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
        count++;

    if (count == 0)
    {
        printf("No movies found.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);
    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
        count++;

    int foundIndex = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Movie not found.\n");
        free(movies);
        return;
    }

    if (!movies[foundIndex].is_rented)
    {
        printf("✗ Movie is not currently rented.\n");
        free(movies);
        return;
    }

    movies[foundIndex].is_rented = 0;
    strcpy(movies[foundIndex].checkout_date, "");

    rewind(fptr);
    for (int i = 0; i < count; i++)
        fwrite(&movies[i], sizeof(Movie), 1, fptr);

    printf("✓ Movie returned successfully!\n");
    free(movies);
}

void showGenreStatistics(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  GENRE STATISTICS                     ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    int count = 0;
    Movie *movies;
    Movie temp;

    rewind(fptr);
    while (fread(&temp, sizeof(Movie), 1, fptr) == 1)
        count++;

    if (count == 0)
    {
        printf("No movies found in library.\n");
        return;
    }

    movies = (Movie *)malloc(count * sizeof(Movie));
    if (movies == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    rewind(fptr);
    count = 0;
    while (fread(&movies[count], sizeof(Movie), 1, fptr) == 1)
        count++;

    printf("Genre-wise breakdown:\n\n");

    for (int i = 0; i < count; i++)
    {
        int genreCount = 1;
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(movies[i].genre, movies[j].genre) == 0)
                genreCount++;
        }

        int isDuplicate = 0;
        for (int j = 0; j < i; j++)
        {
            if (strcmp(movies[i].genre, movies[j].genre) == 0)
            {
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate)
            printf("%s: %d movie(s)\n", movies[i].genre, genreCount);
    }

    free(movies);
}

void exportToCSV(FILE *fptr)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  EXPORT TO CSV                        ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    FILE *csvFile = fopen("movies_export.csv", "w");
    if (csvFile == NULL)
    {
        printf("Error creating CSV file.\n");
        return;
    }

    fprintf(csvFile, "Title,Genre,Year,Director,Language,Rating,Rented,Checkout Date\n");

    Movie movie;
    rewind(fptr);

    int count = 0;
    while (fread(&movie, sizeof(Movie), 1, fptr) == 1)
    {
        fprintf(csvFile, "%s,%s,%d,%s,%s,%d,%s,%s\n",
                movie.title, movie.genre, movie.year, movie.director, movie.language,
                movie.rating, movie.is_rented ? "Yes" : "No", movie.checkout_date);
        count++;
    }

    fclose(csvFile);
    printf("✓ Exported %d movies to 'movies_export.csv' successfully!\n", count);
}

void backupDatabase(void)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  BACKUP DATABASE                      ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    FILE *source = fopen("movies.txt", "rb");
    if (source == NULL)
    {
        printf("No database to backup.\n");
        return;
    }

    FILE *backup = fopen("movies_backup.txt", "wb");
    if (backup == NULL)
    {
        printf("Error creating backup file.\n");
        fclose(source);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0)
        fwrite(buffer, 1, bytes, backup);

    fclose(source);
    fclose(backup);
    printf("✓ Database backed up successfully to 'movies_backup.txt'!\n");
}

void restoreDatabase(void)
{
    CLEAR_SCREEN;
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║  RESTORE DATABASE                     ║\n");
    printf("╚════════════════════════════════════════╝\n\n");

    FILE *backup = fopen("movies_backup.txt", "rb");
    if (backup == NULL)
    {
        printf("No backup file found.\n");
        return;
    }

    FILE *target = fopen("movies.txt", "wb");
    if (target == NULL)
    {
        printf("Error opening target database.\n");
        fclose(backup);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), backup)) > 0)
        fwrite(buffer, 1, bytes, target);

    fclose(backup);
    fclose(target);
    printf("✓ Database restored successfully from backup!\n");
}
