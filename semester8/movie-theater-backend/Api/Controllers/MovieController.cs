using Microsoft.AspNetCore.Mvc;
using Application.Dto;
using Application.Services.Interfaces;

namespace Api.Controllers;

[ApiController]
[Route("api/movies")]
public class MovieController : ControllerBase
{

    private readonly IMovieService _movieService;

    public MovieController(IMovieService movieService)
    {
        _movieService = movieService;    
    }

    [HttpGet]
    public async Task<IEnumerable<MovieDto>> Get(float? minRating)
    {
        return await _movieService.GetMoviesAsync(minRating);
    }

    //[HttpGet("{id}")]
   // public IActionResult Get(int id)
   // {
        
   // }

    [HttpPost]
    public async Task<IActionResult> Post([FromForm]MovieUploadDto movieInfo)
    {
        if (movieInfo.Poster == null)
        {
            return BadRequest("Poster was not uploaded.");
        }

        if (movieInfo.Movie == null || movieInfo.Movie.Length == 0)
        {
            return BadRequest("Movie was not uploaded.");
        }

        await _movieService.UploadMovie(movieInfo);
        return Ok("Movie uploaded successfully.");
    }
}
