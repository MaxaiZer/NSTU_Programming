using Domain.Entities;

namespace Domain.Repositories;

public interface IMovieRepository
{
    public Task<IEnumerable<Movie>> Get(float? minRating);

    public Task Add(Movie movie);

    public void Save();
}