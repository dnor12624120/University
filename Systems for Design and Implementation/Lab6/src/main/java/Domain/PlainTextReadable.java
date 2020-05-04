package Domain;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public interface PlainTextReadable
{
    void readFromFile(BufferedReader reader) throws IOException;
}
