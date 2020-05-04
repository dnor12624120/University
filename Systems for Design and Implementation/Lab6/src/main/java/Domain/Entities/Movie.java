package Domain.Entities;

import Utility.Utility;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import java.io.*;

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
    public void readFromFile(BufferedReader reader) throws IOException
    {
        super.id = Integer.parseInt(reader.readLine());
        this.name = reader.readLine();
        this.genre = reader.readLine();
        this.description = reader.readLine();
    }

    @Override
    public String getEntityTag() {
        return "movie";
    }

    @Override
    public String toString()
    {
        return "Movie\n{" +
                "\t\nname='" + name + '\'' +
                ",\t\ngenre='" + genre + '\'' +
                ",\t\ndescription='" + description + '\'' +
                ",\t\n" + super.toString() +
                "\n}";
    }

    @Override
    public void initializeFromXMLElement(Element element)
    {
        super.id = Integer.parseInt(Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "id")));
        this.name = Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "name"));
        this.genre = Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "genre"));
        this.description = Utility.getValueFromElement(Utility.getSoleElementWithAttribute(element, "description"));
    }

    @Override
    public void appendXMLContentToDocument(Document document, Element root)
    {
        Element movieElement = document.createElement("movie");
        Utility.addAttributeToElement(document, movieElement, "id", super.id.toString());
        Utility.addAttributeToElement(document, movieElement, "name", this.name);
        Utility.addAttributeToElement(document, movieElement, "genre", this.genre);
        Utility.addAttributeToElement(document, movieElement, "description", this.description);
        root.appendChild(movieElement);
    }
}
