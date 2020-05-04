package Domain.Validators;

import java.util.List;
import java.util.Optional;
import java.util.function.Function;

public class GenericValidator<T> implements Validator<T>
{
    private List<Function<T, String>> validatorFunctions;

    public GenericValidator(List<Function<T, String>> validatorFunctions)
    {
        this.validatorFunctions = validatorFunctions;
    }

    @Override
    public void validate(T entity) throws ValidatorException
    {
        String finalErrorMessage = validatorFunctions.
                stream().
                map(predicate -> predicate.apply(entity)).
                reduce("", (acc, message) -> acc + message);
        Optional<String> optional = finalErrorMessage.isEmpty() ? Optional.empty() : Optional.of(finalErrorMessage);
        optional.ifPresent(c -> { throw new ValidatorException(finalErrorMessage); });
    }
}
