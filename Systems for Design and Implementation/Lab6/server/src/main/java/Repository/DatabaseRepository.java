package Repository;

import Domain.DatabaseConfig;
import Domain.Entities.BaseEntity;
import Domain.Validators.RepositoryException;
import Domain.Validators.Validator;
import Domain.Validators.ValidatorException;
import Utility.Sort;
import Utility.SortCriteria;
import Utility.SortOrder;
import javafx.util.Pair;

import java.io.Serializable;
import java.lang.reflect.Field;
import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class DatabaseRepository<ID extends Serializable, T extends BaseEntity<ID>> implements SortingRepository<ID, T>
{
    private DatabaseConfig databaseConfig;
    private Supplier<T> constructor;
    private Validator<T> validator;

    public DatabaseRepository(DatabaseConfig databaseConfig, Supplier<T> constructor, Validator<T> validator) throws NoSuchFieldException
    {
        this.databaseConfig = databaseConfig;
        this.constructor = constructor;
        this.validator = validator;
    }

    @Override
    public Optional<T> findOne(ID id) throws SQLException
    {
        T instance = constructor.get();
        instance.setID(id);
        String sql = "SELECT * FROM " + databaseConfig.tableName + " WHERE id=?";
        Connection connection = getInitializedConnection();
        PreparedStatement statement = connection.prepareStatement(sql);
        completePreparedStatementWithIDField(statement, id);
        ResultSet resultSet = statement.executeQuery();
        resultSet.next();
        T entity = constructor.get();
        try {
            initEntityFromResultSet(entity, resultSet);
        }
        catch (SQLException | IllegalAccessException | NoSuchFieldException ignored)
        {
            return Optional.empty();
        }
        finally {
            connection.close();
        }
        return  Optional.of(entity);
    }

    @Override
    public Iterable<T> findAll() throws SQLException, NoSuchFieldException, IllegalAccessException
    {
        List<T> result = new ArrayList<>();
        String sql = "SELECT * FROM " + databaseConfig.tableName;
        Connection connection = getInitializedConnection();
        PreparedStatement statement = connection.prepareStatement(sql);
        ResultSet resultSet = statement.executeQuery();
        while (resultSet.next())
        {
            T entity = constructor.get();
            initEntityFromResultSet(entity, resultSet);
            result.add(entity);
        }
        connection.close();
        return result;
    }

    private void initEntityFromResultSet(T entity, ResultSet resultSet) throws NoSuchFieldException, SQLException, IllegalAccessException {
        ArrayList<Field> fields = new ArrayList<>(Arrays.asList(entity.getClass().getDeclaredFields()));
        Field idField = entity.getClass().getSuperclass().getDeclaredField("id");
        idField.setAccessible(true);
        idField.set(entity, resultSet.getObject("id"));
        idField.setAccessible(false);
        fields.forEach(field -> {
            try {
                field.setAccessible(true);
                field.set(entity, resultSet.getObject(field.getName()));
                field.setAccessible(false);
            } catch (IllegalAccessException | SQLException e) {
                e.printStackTrace();
            }
        });
    }

    @Override
    public Optional<T> save(T entity) throws ValidatorException, SQLException, IllegalAccessException, NoSuchFieldException, RepositoryException
    {
        Optional<T> foundEntity = findOne(entity.getID());
        foundEntity.<RepositoryException>ifPresent(c -> { throw new RepositoryException("Entity with given ID already exists!"); });
        validator.validate(entity);
        Connection connection = getInitializedConnection();
        String sql = "INSERT INTO " + databaseConfig.tableName + "(" + Utility.Utility.getAllFieldsString(entity) +") VALUES(" + Utility.Utility.getFieldFormatString(entity) + ")";
        try
        {
            PreparedStatement preparedStatement = connection.prepareStatement(sql);
            completePreparedStatementWithAllEntityFields(preparedStatement, entity, 0);
            preparedStatement.executeUpdate();
        }
        catch (SQLException | NullPointerException exception)
        {
            System.out.println(exception.getMessage());
            return Optional.of(entity);
        }
        finally {
            connection.close();
        }
        return Optional.empty();
    }

    private void completePreparedStatementWithAllEntityFields(PreparedStatement preparedStatement, T entity, int idIndex) throws NoSuchFieldException, IllegalAccessException, SQLException {
        ArrayList<Field> fields = new ArrayList<>(Arrays.asList(entity.getClass().getDeclaredFields()));
        Field idField = entity.getClass().getSuperclass().getDeclaredField("id");
        fields.add(idIndex, idField);
        ArrayList<Pair<Integer, Field>> fieldIndexPairs = new ArrayList<>();
        IntStream.rangeClosed(1, fields.size()).forEach(i -> fieldIndexPairs.add(new Pair<>(i, fields.get(i - 1))));
        fieldIndexPairs.forEach(pair -> {
            try {
                pair.getValue().setAccessible(true);
                preparedStatement.setObject(pair.getKey(), pair.getValue().get(entity));
                pair.getValue().setAccessible(false);
            } catch (SQLException | IllegalAccessException e) {
                e.printStackTrace();
            }
        });
    }

    @Override
    public Optional<T> delete(ID id) throws SQLException, RepositoryException
    {
        Optional<T> entity = findOne(id);
        entity.<RepositoryException>orElseThrow(() -> { throw new RepositoryException("No entity with given ID found!"); });
        String sql = "DELETE FROM " + databaseConfig.tableName + " WHERE id=?";
        Connection connection = getInitializedConnection();
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        completePreparedStatementWithIDField(preparedStatement, id);
        preparedStatement.executeUpdate();
        connection.close();
        return entity;
    }

    private void completePreparedStatementWithIDField(PreparedStatement preparedStatement, ID id)
    {
        try
        {
            preparedStatement.setObject(1, id);
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<T> update(T entity) throws ValidatorException, SQLException, NoSuchFieldException, IllegalAccessException {
        validator.validate(entity);
        Optional<T> optional = findOne(entity.getID());
        optional.<RepositoryException>orElseThrow(() -> { throw new RepositoryException("No entity with given ID found!"); });
        String sql = "UPDATE " + databaseConfig.tableName + " SET " + Utility.Utility.getNonIDFieldsFormattedString(entity) + " WHERE id=?";
        System.out.println(sql);
        Connection connection = getInitializedConnection();
        PreparedStatement preparedStatement = connection.prepareStatement(sql);
        completePreparedStatementWithAllEntityFields(preparedStatement, entity, entity.getClass().getDeclaredFields().length);
        preparedStatement.executeUpdate();
        connection.close();
        return optional;
    }

    @Override
    public Iterable<T> findAll(Sort sort) throws SQLException, NoSuchFieldException, IllegalAccessException {
        ArrayList<T> allEntities = (ArrayList<T>) Utility.Utility.iterableToList(findAll());
        allEntities.sort((entity1, entity2) -> {
            for(SortCriteria criteria : sort.getSortCriteria()) {
                //since our domain entities only have plain old data fields, we can compare
                //them by casting them to strings (not an ideal solution)
                try {
                    Field field1 = entity1.getClass().getDeclaredField(criteria.field);
                    Field field2 = entity2.getClass().getDeclaredField(criteria.field);
                    field1.setAccessible(true);
                    field2.setAccessible(true);
                    String e1Field = field1.get(entity1).toString();
                    String e2Field = field2.get(entity2).toString();

                    field1.setAccessible(true);
                    field2.setAccessible(true);
                    int compareResult = criteria.order == SortOrder.ASCENDING ? e1Field.compareTo(e2Field) : -e1Field.compareTo(e2Field);
                    if(compareResult != 0)
                    {
                        return compareResult;
                    }
                } catch (NoSuchFieldException | IllegalAccessException e) {
                    e.printStackTrace();
                }
            }
            return 0;
        });
        return allEntities;
    }

    @Override
    public Iterable<T> filter(Predicate<T> predicate) throws SQLException, NoSuchFieldException, IllegalAccessException {
        List<T> entities = Utility.Utility.iterableToList(findAll());
        return entities.stream().filter(predicate).collect(Collectors.toList());
    }

    private Connection getInitializedConnection() throws SQLException {
        return DriverManager.getConnection(databaseConfig.databaseURL, databaseConfig.username, databaseConfig.password);
    }
}
