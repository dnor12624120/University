package Domain.Entities;

import java.io.Serializable;

public class Movie extends BaseEntity<Integer> implements Serializable
{
    private String name;
    private String genre;
    private String description;

    public Movie()
    {
    }

    public Movie(String name, String genre, String description)
    {
        this.name = name;
        this.genre = genre;
        this.description = description;
    }

    public String getName() {
        return name;
    }
    public String getGenre() { return genre; }
    public String getDescription() { return description; }
    public void setName(String name) {
        this.name = name;
    }
    public void setGenre(String genre) {
        this.genre = genre;
    }
    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public boolean equals(Object object)
    {
        if (this == object)
        {
            return true;
        }
        if (object == null || getClass() != object.getClass())
        {
            return false;
        }

        Movie movie = (Movie) object;
        if (!genre.equals(movie.genre))
        {
            return false;
        }
        if (!description.equals(movie.description))
        {
            return false;
        }
        return name.equals(movie.name);
    }

    @Override
    public String toString()
    {
        return id + " " + name + " " + genre + " " + description;
    }
}
